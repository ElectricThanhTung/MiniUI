using MiniUI.Properties;
using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;
using System.Xml;

namespace MiniUI {
    public partial class App : Application {
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool FreeConsole();

        [DllImport("kernel32", SetLastError = true)]
        static extern bool AttachConsole(int dwProcessId);

        private void AppStartup(object sender, StartupEventArgs e) {
            if(e.Args.Length > 0) {
                AttachConsole(-1);
                try {
                    int argIndex = 0;
                    string sources = null;
                    string[] option = new string[2];

                    foreach(string arg in e.Args) {
                        if(arg[0] == '-') {
                            switch(arg) {
                                case "-c":
                                case "--config":
                                    argIndex = 1;
                                    break;
                                case "-o":
                                case "--output":
                                    argIndex = 2;
                                    break;
                                default:
                                    throw new Exception("unknown option: " + arg);
                            }
                        }
                        else {
                            if(argIndex > 0) {
                                option[argIndex - 1] = arg;
                                argIndex = 0;
                            }
                            else if(sources == null || sources == "")
                                sources = arg;
                            else
                                throw new Exception("unknown option: " + arg);
                        }
                    }
                    if(sources == null || sources == "")
                        throw new Exception("no input file");
                    if(option[0] == null || option[0] == "")
                        throw new Exception("no config file");
                    if(option[1] == null || option[1] == "")
                        option[1] = Path.GetFileNameWithoutExtension(sources) + ".cpp";

                    MiniUIXml miniUIXml = new MiniUIXml(sources, option[0]);
                    miniUIXml.Genarate(option[1]);
                    Environment.ExitCode = 0;
                }
                catch(MiniUIXmlException exp) {
                    ShowError(exp);
                    Environment.ExitCode = 1;
                }
                catch(Exception exp) {
                    ShowError(exp.Message);
                    Environment.ExitCode = 1;
                }
                FreeConsole();
                Application.Current.Shutdown();
            }
            else
                new MainWindow().Show();
        }

        private void ShowError(string msg) {
            ConsoleColor console = Console.ForegroundColor;
            Console.Error.Write("MiniUI.exe: ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Error.Write("error: ");
            Console.ForegroundColor = console;
            Console.Error.WriteLine(msg);
        }

        private void ShowError(MiniUIXmlException e) {
            ConsoleColor console = Console.ForegroundColor;
            Console.Error.Write(e.File + ":" + e.LineNumber + ":" + e.LinePosition + ": ");
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Error.Write("error: ");
            Console.ForegroundColor = console;
            Console.Error.WriteLine(e.Message);
        }
    }
}
