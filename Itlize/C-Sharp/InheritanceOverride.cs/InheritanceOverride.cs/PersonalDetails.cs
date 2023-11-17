
using System;
using System.Collections.Generic;
using System.Linq;

namespace InheritanceOverride.cs
{
	class PersonalDetails
	{
		public string firstname { get; set; }
		public string lastname { get; set; }
		public int age { get; set; }
		public string gender { get; set; }
	}
	class Program{
		static void Main(string[] args)
		{
			//create a list to store personal details obj
			List<PersonalDetails> mylist = new List<PersonalDetails>();

            //add objs about personal detail to the list
            mylist.Add(new PersonalDetails { firstname = "Mihir", lastname = "Tomar", age=19, gender="M"});
			mylist.Add(new PersonalDetails { firstname = "Anil", lastname = "Tomar", age = 50, gender = "M" });
			mylist.Add(new PersonalDetails { firstname = "Sujata", lastname = "Mahale", age = 45, gender = "F" });


			//print all the items in the list
			foreach(PersonalDetails i in mylist)
			{
				Console.WriteLine($"Name: {i.firstname} {i.lastname}, Age: {i.age}, gender: {i.gender}");
			}

			//filter list using condition age>35
			List<PersonalDetails> filterList = mylist.Where(i => i.age > 35).ToList();

			//sort the list on the first name
			filterList.Sort((i, j) => i.firstname.CompareTo(j.firstname));

            //print this sorted and filtered list
            Console.WriteLine("\nFilter/Sort result: ");
            foreach (PersonalDetails i in filterList)
            {
                Console.WriteLine($"Name: {i.firstname} {i.lastname}, Age: {i.age}, Gender: {i.gender}");
            }

            //create new list of other new obj
            List<PersonalDetails> newlist = new List<PersonalDetails>
			{
				new PersonalDetails { firstname = "Ann", lastname = "Abrahamson", age = 43, gender = "F" },
				new PersonalDetails { firstname = "Jack", lastname = "Goodrich", age = 51, gender = "M" }
			};

            //add new list to the current one
            mylist.AddRange(newlist);

            //remove the male employees from the list
            mylist.RemoveAll(i => i.gender == "M");

            //print the final list after removal to show the result
            Console.WriteLine("\nFinal result: ");
            foreach (PersonalDetails i in mylist)
            {
                Console.WriteLine($"Name: {i.firstname} {i.lastname}, Age: {i.age}, Gender: {i.gender}");
            }
        }
    }
}