using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MiniUI {
    internal class LineException : Exception {
        public LineException(string message, int lineNumber, int linePosition) : base(message) {
            LineNumber = lineNumber;
            LinePosition = linePosition;
        }

        public int LineNumber {
            get; private set;
        }

        public int LinePosition {
            get; private set;
        }
    }
}
