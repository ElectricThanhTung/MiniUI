using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Linq;

namespace MiniUI {
    public class MiniUIXml {
        private string guiFile;
        private StringBuilder declarationCode;
        private StringBuilder initializeCode;
        private Dictionary<string, int> controlNameIndex;
        private Dictionary<string, ControlInfo> controlInfos;

        private readonly string[] colorList = {
            "Black", "Silver", "Gray", "White", "Maroon", "Red", "Purple", "Fuchsia", "Green", "Lime", "Olive", "Yellow", "Navy",
            "Blue", "Teal", "Aqua", "Orange", "AliceBlue", "AntiqueWhite", "Aquamarine", "Azure", "Beige", "Bisque", "BlanchedAlmond",
            "BlueViolet", "Brown", "Burlywood", "CadetBlue", "Chartreuse", "Chocolate", "Coral", "CornflowerBlue", "Cornsilk",
            "Crimson", "Cyan", "DarkBlue", "DarkCyan", "DarkGoldenrod", "DarkGray", "DarkGreen", "DarkGrey", "DarkKhaki",
            "DarkMagenta", "DarkOliveGreen", "DarkOrange", "DarkOrchid", "DarkRed", "DarkSalmon", "DarkSeaGreen", "DarkSlateBlue",
            "DarkSlateGray", "DarkSlateGrey", "DarkTurquoise", "DarkViolet", "DeepPink", "SeepSkyBlue", "DimGray", "DimGrey",
            "DodgerBlue", "Firebrick", "FloralWhite", "ForestGreen", "Gainsboro", "GhostWhite", "Gold", "Goldenrod", "GreenYellow",
            "Grey", "Honeydew", "HotPink", "IndianRed", "Indigo", "Ivory", "Khaki", "Lavender", "LavenderBlush", "LawnGreen",
            "LemonChiffon", "LightBlue", "LightCoral", "LightCyan", "LightGoldenrodYellow", "LightGray", "LightGreen", "LightGrey",
            "LightPink", "LightSalmon", "LightSeaGreen", "LightSkyBlue", "LightSlateGray", "LightSlateGrey", "LightSteelBlue",
            "LightYellow", "LimeGreen", "Linen", "Magenta", "MediumAquamarine", "MediumBlue", "MediumOrchid", "MediumPurple",
            "MediumSeaGreen", "MediumSlateBlue", "MediumSpringGreen", "MediumTurquoise", "MediumVioletRed", "MidnightBlue",
            "MintCream", "MistyRose", "Moccasin", "NavajoWhite", "OldLace", "OliveDrab", "OrangeRed", "Orchid", "PaleGoldenrod",
            "PaleGreen", "PaleTurquoise", "PaleVioletRed", "PapayaWhip", "PeachPuff", "Peru", "Pink", "Plum", "PowderBlue",
            "RosyBrown", "RoyalBlue", "SaddleBrown", "Salmon", "SandyBrown", "SeaGreen", "SeaShell", "Sienna", "SkyBlue",
            "SlateBlue", "SlateGray", "Snow", "SpringGreen", "SteelBlue", "Tan", "Thistle", "Tomato", "Turquoise", "Violet",
            "Wheat", "WhiteSmoke", "YellowGreen", "Transparent"
        };

        enum PropertyType {
            Raw,
            Boolean,
            Interger,
            String,
            Color,
            Object
        }

        private class PropertyInfo {
            public string Name = null;
            public int[] Param = null;
            public string Method = null;
            public object[] Type = null;
        }

        private class ControlInfo {
            public string Name = null;
            public bool MultipleContent = false;
            public string ContentProperty = null;
            public bool UseGeneral = true;
            public Dictionary<string, PropertyInfo> Properties = null;
        }

        public MiniUIXml(string guiFile, string configFile) {
            declarationCode = new StringBuilder();
            initializeCode = new StringBuilder();
            controlNameIndex = new Dictionary<string, int>();
            this.guiFile = guiFile;
            ReadConfigFile(configFile);
        }

        private void ReadConfigFile(string configFile) {
            XElement config = XElement.Load(configFile, LoadOptions.SetLineInfo);

            try {
                if(config.Name != "MiniUI") {
                    IXmlLineInfo lineInfo = config;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    throw new LineException("root node is not MiniUI tag", line, pos);
                }

                Dictionary<string, PropertyInfo> generalProperties = null;
                controlInfos = null;

                foreach(XElement node in config.Elements()) {
                    if(node.Name == "General")
                        generalProperties = ReadGeneralProperties(node);
                    else if(node.Name == "Specific")
                        controlInfos = ReadControlInfo(node);
                    else {
                        IXmlLineInfo lineInfo = node;
                        int line = lineInfo.LineNumber;
                        int pos = lineInfo.LinePosition;
                        throw new LineException("'" + node.Name + "' unknow the config", line, pos);
                    }
                }
                foreach(ControlInfo control in controlInfos.Values) {
                    if(control.UseGeneral) {
                        for(int i = 0; i < generalProperties.Count; i++) {
                            KeyValuePair<string, PropertyInfo> keyValuePair = generalProperties.ElementAt(i);
                            if(!control.Properties.ContainsKey(keyValuePair.Key))
                                control.Properties.Add(keyValuePair.Key, keyValuePair.Value);
                        }
                    }
                }
            }
            catch(XmlException e) {
                throw new MiniUIXmlException(configFile, e.Message, e.LineNumber, e.LinePosition);
            }
            catch(LineException e) {
                throw new MiniUIXmlException(configFile, e);
            }
        }

        private object[] ReadPropertyType(XElement propertyTypes) {
            List<object> ret = new List<object>();
            List<string> typeList = new List<string>();
            foreach(XElement node in propertyTypes.Elements()) {
                if(typeList.Contains(node.Name.LocalName)) {
                    IXmlLineInfo lineInfo = node;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    throw new LineException("'" + node.Name + "' duplicate the type", line, pos);
                }
                typeList.Add(node.Name.LocalName);
                switch(node.Name.LocalName) {
                    case "Raw":
                        ret.Add(PropertyType.Raw);
                        break;
                    case "Boolean":
                        ret.Add(PropertyType.Boolean);
                        break;
                    case "Interger":
                        ret.Add(PropertyType.Interger);
                        break;
                    case "String":
                        ret.Add(PropertyType.String);
                        break;
                    case "Color":
                        ret.Add(PropertyType.Color);
                        break;
                    case "Object":
                        ret.Add(PropertyType.Object);
                        break;
                    case "Enum": {
                        Dictionary<string, string> valuePairs = new Dictionary<string, string>();
                        foreach(XElement enumValue in node.Elements()) {
                            if(!valuePairs.ContainsKey(enumValue.Name.LocalName))
                                valuePairs.Add(enumValue.Name.LocalName, enumValue.Attribute("Value").Value);
                            else {
                                IXmlLineInfo lineInfo = enumValue;
                                int line = lineInfo.LineNumber;
                                int pos = lineInfo.LinePosition;
                                throw new LineException("'" + enumValue.Name + "' duplicate the value", line, pos);
                            }
                        }
                        ret.Add(valuePairs);
                        break;
                    }
                    default: {
                        IXmlLineInfo lineInfo = node;
                        int line = lineInfo.LineNumber;
                        int pos = lineInfo.LinePosition;
                        throw new LineException("'" + node.Name + "' unknow the type", line, pos);
                    }
                }
            }
            return ret.ToArray();
        }

        private bool IsContainsType(object[] types, PropertyType type) {
            foreach(object t in types) {
                if(t.GetType() == typeof(PropertyType) && (PropertyType)t == type)
                    return true;
            }
            return false;
        }

        private bool IsSupportMultiParam(int[] param) {
            foreach(int p in param) {
                if(p > 1)
                    return true;
            }
            return false;
        }

        private bool IsColor(string str) {
            foreach(string s in colorList) {
                if(s == str)
                    return true;
            }
            return false;
        }

        private Dictionary<string, string> GetEnumType(object[] types) {
            foreach(object type in types) {
                if(type.GetType() == typeof(Dictionary<string, string>))
                    return (Dictionary<string, string>)type;
            }
            return null;
        }

        private Dictionary<string, PropertyInfo> ReadGeneralProperties(XElement generalCfg) {
            Dictionary<string, PropertyInfo> ret = new Dictionary<string, PropertyInfo>();
            foreach(XElement node in generalCfg.Elements()) {
                IXmlLineInfo lineInfo = node;
                int line = lineInfo.LineNumber;
                int pos = lineInfo.LinePosition;
                if(!ret.ContainsKey(node.Name.LocalName)) {
                    int[] param = null;
                    if(node.Attribute("Param") != null) {
                        string temp = node.Attribute("Param").Value.Replace(",", " ").Replace("  ", " ");
                        string[] paramStr = temp.Split(' ');
                        param = new int[paramStr.Length];
                        for(int i = 0; i < paramStr.Length; i++)
                            param[i] = int.Parse(paramStr[i]);
                    }
                    PropertyInfo property = new PropertyInfo();
                    property.Name = node.Name.LocalName;
                    property.Param = param;
                    property.Method = node.Attribute("Method").Value;
                    property.Type = ReadPropertyType(node);
                    if(IsContainsType(property.Type, PropertyType.String)) {
                        if(IsSupportMultiParam(property.Param))
                            throw new LineException("multiple param not support for String type", line, pos);
                        if((property.Type.Length > 2) || (property.Type.Length == 2 && !IsContainsType(property.Type, PropertyType.Object)))
                            throw new LineException("string types cannot be overloaded with other data types except object types", line, pos);
                    }
                    ret.Add(node.Name.LocalName, property);
                }
                else
                    throw new LineException("'" + node.Name + "' duplicate the property", line, pos);
            }
            return ret;
        }

        private Dictionary<string, ControlInfo> ReadControlInfo(XElement controlConfig) {
            Dictionary<string, ControlInfo> ret = new Dictionary<string, ControlInfo>();
            foreach(XElement node in controlConfig.Elements()) {
                if(!ret.ContainsKey(node.Name.LocalName)) {
                    ControlInfo control = new ControlInfo();
                    control.Name = node.Name.LocalName;
                    control.MultipleContent = node.Attribute("MultipleContent") != null ? bool.Parse(node.Attribute("MultipleContent").Value) : false;
                    control.ContentProperty = node.Attribute("ContentProperty") != null ? node.Attribute("ContentProperty").Value : null;
                    control.UseGeneral = node.Attribute("UseGeneral") != null ? bool.Parse(node.Attribute("UseGeneral").Value) : true;
                    control.Properties = ReadGeneralProperties(node);
                    ret.Add(node.Name.LocalName, control);
                }
                else {
                    IXmlLineInfo lineInfo = node;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    throw new LineException("'" + node.Name + "' duplicate control", line, pos);
                }
            }
            return ret;
        }

        private string AddDeclarationCode(XElement controlNode) {
            string controlName;
            string controlType = controlNode.Name.LocalName;
            XAttribute nameAttr = controlNode.Attribute("Name");
            if(!controlNameIndex.ContainsKey(controlType))
                controlNameIndex.Add(controlType, 1);
            if(nameAttr != null && nameAttr.Value.Trim() != "") {
                if(Regex.Match(nameAttr.Value, @"^[a-zA-Z_]\w*$").Value != "")
                    controlName = nameAttr.Value;
                else {
                    IXmlLineInfo lineInfo = nameAttr;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    pos += nameAttr.ToString().Substring(nameAttr.Name.LocalName.Length).IndexOf(nameAttr.Value);
                    pos += nameAttr.Name.LocalName.Length;
                    throw new LineException("'" + nameAttr.Value + "' class name is invalid", line, pos);
                }
            }
            else {
                int index = controlNameIndex[controlType];
                controlName = controlType.ToLower() + index;
                controlNameIndex[controlType] = index + 1;
            }

            declarationCode.AppendLine(controlType + " " + controlName + ";");

            return controlName;
        }

        private (string, XElement) GenarateObject(XElement node, bool isRootNode) {
            ControlInfo controlInfo = controlInfos[node.Name.LocalName];
            List<(string, XNode)> childrenList = new List<(string, XNode)>();
            int contentInAttribute = 0;
            IEnumerable<XNode> children = node.Nodes();
            if(children != null && children.Count() > 0) {
                foreach(XNode control in children) {
                    if(control.NodeType == XmlNodeType.Element)
                        childrenList.Add(GenarateObject((XElement)control, false));
                    else if(control.NodeType == XmlNodeType.Text)
                        childrenList.Add((control.ToString().Trim(), control));
                }
            }
            string controlName = isRootNode ? "this" : AddDeclarationCode(node);
            string prefix = controlName + (isRootNode ? "->" : ".");
            foreach(XAttribute attribute in node.Attributes()) {
                if(attribute.Name != "Name" && attribute.Name != "Class") {
                    if(!controlInfo.Properties.ContainsKey(attribute.Name.LocalName)) {
                        IXmlLineInfo lineInfo = attribute;
                        int line = lineInfo.LineNumber;
                        int pos = lineInfo.LinePosition;
                        throw new LineException("'" + attribute.Name + "' does not support in '" + node.Name + "' control", line, pos);
                    }
                    PropertyInfo propertyInfo = controlInfo.Properties[attribute.Name.LocalName];
                    if(attribute.Name == controlInfo.ContentProperty)
                        contentInAttribute++;
                    if(IsContainsType(propertyInfo.Type, PropertyType.String))
                        initializeCode.AppendLine(prefix + propertyInfo.Method + "(\"" + attribute.Value + "\");");
                    else {
                        string[] paramValues = attribute.Value.Replace(",", " ").Trim().Replace("  ", " ").Split(' ');
                        bool isOk = false;
                        foreach(int p in propertyInfo.Param) {
                            if(paramValues.Length == p)
                                isOk = true;
                        }
                        if(!isOk) {
                            IXmlLineInfo lineInfo = attribute;
                            int line = lineInfo.LineNumber;
                            int pos = lineInfo.LinePosition;
                            pos += attribute.ToString().Substring(attribute.Name.LocalName.Length).IndexOf(attribute.Value);
                            pos += attribute.Name.LocalName.Length;
                            throw new LineException("'" + attribute.Value + "' property does not support passing in " + paramValues.Length + " operands", line, pos);
                        }
                        if(paramValues.Length > 0) {
                            initializeCode.Append(prefix + propertyInfo.Method + "(");
                            for(int i = 0; i < paramValues.Length; i++) {
                                int num = 0;
                                bool b = false;
                                if(i > 0)
                                    initializeCode.Append(", ");
                                if(IsContainsType(propertyInfo.Type, PropertyType.Interger) && int.TryParse(paramValues[i], out num))
                                    initializeCode.Append(paramValues[i]);
                                else if(IsContainsType(propertyInfo.Type, PropertyType.Boolean) && bool.TryParse(paramValues[i], out b))
                                    initializeCode.Append(paramValues[i].ToLower());
                                else if(IsContainsType(propertyInfo.Type, PropertyType.Raw) && Regex.Match(paramValues[i], @"^[a-zA-Z_]\w*$").Value != "")
                                    initializeCode.Append(paramValues[i]);
                                else if(IsContainsType(propertyInfo.Type, PropertyType.Color) && IsColor(paramValues[i]))
                                    initializeCode.Append("Color::" + paramValues[i]);
                                else {
                                    Dictionary<string, string> enumType = GetEnumType(propertyInfo.Type);
                                    if(enumType != null && enumType.ContainsKey(paramValues[i]))
                                        initializeCode.Append(enumType[paramValues[i]]);
                                    else {
                                        IXmlLineInfo lineInfo = attribute;
                                        int line = lineInfo.LineNumber;
                                        int pos = lineInfo.LinePosition;
                                        pos += attribute.ToString().Substring(attribute.Name.LocalName.Length).IndexOf(paramValues[i]);
                                        pos += attribute.Name.LocalName.Length;
                                        throw new LineException("'" + paramValues[i] + "' unknow the value", line, pos);
                                    }
                                }
                            }
                            initializeCode.AppendLine(");");
                        }
                    }
                }
            }
            if(childrenList.Count > 0) {
                if(controlInfo.MultipleContent || (childrenList.Count + contentInAttribute) == 1) {
                    PropertyInfo contentProperty = controlInfo.Properties[controlInfo.ContentProperty];
                    foreach((string, XNode) child in childrenList) {
                        IXmlLineInfo lineInfo = child.Item2;
                        int line = lineInfo.LineNumber;
                        int pos = lineInfo.LinePosition;
                        if(child.Item2.NodeType == XmlNodeType.Element) {
                            if(IsContainsType(contentProperty.Type, PropertyType.Object))
                                initializeCode.AppendLine(prefix + contentProperty.Method + "(" + child.Item1 + ");");
                            else
                                throw new LineException("'" + child.Item1 + "' cannot pass an object to the '" + node.Name + "'", line, pos);
                        }
                        else {
                            if(IsContainsType(contentProperty.Type, PropertyType.String))
                                initializeCode.AppendLine(prefix + contentProperty.Method + "(\"" + child.Item1 + "\");");
                            else
                                throw new LineException("'" + child.Item1 + "' cannot pass an string to the '" + node.Name + "'", line, pos);
                        }
                    }
                }
                else {
                    XNode errorNode = childrenList[1].Item2;
                    string temp = (errorNode.NodeType == XmlNodeType.Element) ? ((XElement)errorNode).Name.LocalName : errorNode.ToString().Trim();
                    IXmlLineInfo lineInfo = childrenList[1].Item2;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition + errorNode.ToString().IndexOf(temp);
                    throw new LineException("'" + temp + "' doesn't support multiple content", line, pos);
                }
            }
            initializeCode.AppendLine();
            return (isRootNode ? null : controlName, node);
        }

        private string InsertTab(string code, int tab = 1) {
            StringBuilder builder = new StringBuilder();
            string[] lines = code.Replace("\r", "").Split('\n');
            for(int i = 0; i < lines.Length; i++) {
                if(i > 0)
                    builder.AppendLine();
                for(int t = 0; t < tab; t++)
                    builder.Append("    ");
                builder.Append(lines[i]);
            }
            return builder.ToString();
        }

        private void CreateSourceFile(string fileName, string rootName, string className) {
            StreamWriter writer = new StreamWriter(fileName);
            string define = "__MINIUI_" + className.ToUpper() + "_H";

            writer.WriteLine("#ifndef " + define);
            writer.WriteLine("#define " + define);
            writer.WriteLine();
            writer.WriteLine("#include \"miniui.h\"");
            writer.WriteLine();
            writer.WriteLine("class " + className + " : public " + rootName + " {");
            writer.WriteLine("public:");
            writer.WriteLine(InsertTab(declarationCode.ToString().Trim()));
            writer.WriteLine("public:");
            writer.WriteLine("    " + className + "() {");
            writer.WriteLine(InsertTab(initializeCode.ToString().Trim(), 2));
            writer.WriteLine("    }");
            writer.WriteLine("};");
            writer.WriteLine();
            writer.WriteLine("#endif /* " + define + " */");

            writer.Close();
        }

        public void Genarate(string fileName) {
            try {
                XElement xElement = XElement.Load(guiFile, LoadOptions.SetLineInfo);
                string rootName = xElement.Name.LocalName;
                string className = xElement.Attribute("Class")?.Value;

                declarationCode.Clear();
                initializeCode.Clear();
                controlNameIndex.Clear();

                if(className == null) {
                    IXmlLineInfo lineInfo = xElement;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    throw new LineException("'" + rootName + "' need to name class", line, pos);
                }
                if(className.Trim() == "") {
                    IXmlLineInfo lineInfo = xElement.Attribute("Class");
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    throw new LineException("'Class' name is invalid", line, pos);
                }
                else if(Regex.Match(className, @"^[a-zA-Z_]\w*$").Value == "") {
                    XAttribute attribute = xElement.Attribute("Class");
                    IXmlLineInfo lineInfo = attribute;
                    int line = lineInfo.LineNumber;
                    int pos = lineInfo.LinePosition;
                    pos += attribute.ToString().Substring(attribute.Name.LocalName.Length).IndexOf(attribute.Value);
                    pos += attribute.Name.LocalName.Length;
                    throw new LineException("'" + className + "' class name is invalid", line, pos);
                }

                GenarateObject(xElement, true);
                CreateSourceFile(fileName, rootName, className);
            }
            catch(XmlException e) {
                throw new MiniUIXmlException(guiFile, e.Message, e.LineNumber, e.LinePosition);
            }
            catch(LineException e) {
                throw new MiniUIXmlException(guiFile, e);
            }
        }
    }
}
