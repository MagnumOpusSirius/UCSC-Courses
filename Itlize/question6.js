function range(a, b) {
    const res = [];
    // Check if the range is valid
    if (a >= b - 1) {
      return res;
    }
    // Populate the result array with integers in the range
    for (let i = a + 1; i < b; i++) {
      res.push(i);
    }
    return res;
  }
  
  // Example:
  const a = 2;
  const b = 9;
  console.log("Example: range("+a+","+b+")");
  const res = range(a, b);
  console.log("Example output: ["+res+"]");