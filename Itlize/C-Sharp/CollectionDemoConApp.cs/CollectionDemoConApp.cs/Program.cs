// See https://aka.ms/new-console-template for more information
using System;
using System.Collections.Generic;

public class Employee
{
    public Employee(int id, string name)
    {
        EmpId = id;
        EmpName = name;
    }

    private int _EmpId;

    public int EmpId
    {
        get { return _EmpId; }
        set { _EmpId = value; }
    }

    private string _EmpName;

    public string EmpName
    {
        get { return _EmpName; }
        set { _EmpName = value; }
    }
}

class Program
{
    static void Main(string[] args)
    {
        //create a dict to keep track of employee record
        Dictionary<int, Employee> emp = new Dictionary<int, Employee>();

        // as per the script add 5 emp record to dict
        emp.Add(1, new Employee(1, "Brandon"));
        emp.Add(2, new Employee(2, "Kenny"));
        emp.Add(3, new Employee(3, "Ruben"));
        emp.Add(4, new Employee(4, "Michael"));
        emp.Add(5, new Employee(5, "Anika"));

        //print the result of the emp record in the dict
        Console.WriteLine("Here are the details of employee:");
        foreach (var i in emp)
        {
            Console.WriteLine($"Employee ID: {i.Key}, Name: {i.Value.EmpName}");
        }
    }
}