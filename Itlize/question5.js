function findSecLowGreat(numbers) {
    // we sort in ascending order
    const sortedArray = numbers.sort(function(a, b) {
      return a - b;
    });
  
    // now find the second lowest and second greatest numbers
    const secondLowest = sortedArray[1];
    const secondGreatest = sortedArray[sortedArray.length - 2];
  
    return [secondLowest, secondGreatest];
  }
  
  // Example
  const array = [1, 2, 3, 4, 5];
  console.log("sample array: "+ array);
  const result = findSecLowGreat(array);
  console.log("expected output: "+ result.join(', '));