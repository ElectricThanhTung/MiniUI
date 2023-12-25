using System;
using System.Xml;

namespace MiniUI {
    internal class MiniUIXmlException : LineException {
        public MiniUIXmlException(string file, LineException lineException) : base(lineException.Message, lineException.LineNumber, lineException.LinePosition) {
            File = file;
        }

        public MiniUIXmlException(string file, string message, int lineNumber, int linePosition) : base(message, lineNumber, linePosition) {
            File = file;
        }

        public string File {
            get; private set;
        }
    }
}
