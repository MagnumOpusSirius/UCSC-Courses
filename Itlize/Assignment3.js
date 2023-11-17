// Get the current date and time
const currentDate = new Date();

// get the data
const year = currentDate.getFullYear();
const month = (currentDate.getMonth() + 1).toString().padStart(2, '0');
const day = currentDate.getDate().toString().padStart(2, '0');

// Format the date
const date1 = month + '-' + day + '-' + year; // mm-dd-yyyy

// Display
console.log('mm-dd-yyyy: ' + date1);



