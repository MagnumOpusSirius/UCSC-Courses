using System;
class Exercise1{
    public static void Main(){
        int[] arr= {1, 1, 1,1, 3, 3, 4, 5, 6, 1};
        //to store the occurences of each element
        Dictionary<int, int> data=new Dictionary<int, int>();
        foreach(int elem in arr){
            if(data.ContainsKey(elem)){
                data[elem]++;
            }
            else{
                data[elem]=1;
            }
        }
        int maxFreq=0;
        foreach(int value in data.Values){
            if(value>maxFreq){
                maxFreq=value;
            }
        }
        //Console.Write(maxFreq);
        //Console.WriteLine();
        foreach(var i in data){
            if (i.Value==maxFreq){
                Console.WriteLine("the most repeated element is: "+i.Key);
            }
        }
    }
}