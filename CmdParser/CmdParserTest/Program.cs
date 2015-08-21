using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CmdParser;

namespace CmdParserTest
{
    class Program
    {
        static CCmdParser m_parser;

        static int Main(string[] args)
        {
            Dictionary<String, KeyValuePair<EArgType, bool>> argList = new Dictionary<String, KeyValuePair<EArgType, bool>>();
            argList.Add("-p", new KeyValuePair<EArgType, bool>(EArgType.VALUE, true));
            argList.Add("-u", new KeyValuePair<EArgType, bool>(EArgType.VALUE, true));
            argList.Add("-v", new KeyValuePair<EArgType, bool>(EArgType.VALUE, false));
            argList.Add("-o", new KeyValuePair<EArgType, bool>(EArgType.FLAG, false));
            m_parser = new CCmdParser(argList);
            if(!m_parser.Parse(args))
            {
                foreach (String arg in m_parser.Options.Keys)
                {
                    Console.WriteLine(arg + " = " + m_parser.Options[arg]);
                }
                Usage();
                return 1;
            }
            foreach(String arg in m_parser.Options.Keys)
            {
                Console.WriteLine(arg + " = " + m_parser.Options[arg]);
            }
            return 0;
        }

        static void Usage()
        {
            Console.WriteLine("-p path       required");
            Console.WriteLine("-u user       required");
            Console.WriteLine("-v version    not required");
            Console.WriteLine("-o overwrite  not required");
        }
    }
}
