function mergeSort(array) {
    // if arr has one elem return that array
    if (array.length <= 1) {
      return array;
    }
    const middle = Math.floor(array.length / 2);// get the middle index
    
    const left = array.slice(0, middle); //split array into 2 from 0 to middle and middle to right
    const right = array.slice(middle);
    
    const sortedLeft = mergeSort(left); //recursive call for left and right array
    const sortedRight = mergeSort(right);
    
    return merge(sortedLeft, sortedRight); //merge call to left and right
  }
function merge(left, right) {
    const mergedArray = [];
    let leftIndex = 0;
    let rightIndex = 0;
    
    // Merge two arr into one
    while (leftIndex < left.length && rightIndex < right.length) {
      if (left[leftIndex] < right[rightIndex]) {
        mergedArray.push(left[leftIndex]);
        leftIndex++;
      } else {
        mergedArray.push(right[rightIndex]);
        rightIndex++;
      }
    }
    // get left array
    while (leftIndex < left.length) {
      mergedArray.push(left[leftIndex]);
      leftIndex++;
    }
    // get right array
    while (rightIndex < right.length) {
      mergedArray.push(right[rightIndex]);
      rightIndex++;
    }
    return mergedArray;
}
const array = [34, 7, 23, 32, 5, 62];
console.log('Sample array: ' + array);
const sortedArray = mergeSort(array);
console.log('Sample output: ' + sortedArray);