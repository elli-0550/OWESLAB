using System;
using System.Diagnostics;
class Program
{
static void Main(string[] args)
{
Console.WriteLine("\n Process ID is: " + Process.GetCurrentProcess().Id);
try
{
Process p = Process.Start("whoami");
p.WaitForExit();
}
catch (Exception ex)
{
Console.WriteLine("Failed to start process: " + ex.Message);
Environment.Exit(1);
}
Environment.Exit(0);
}
}