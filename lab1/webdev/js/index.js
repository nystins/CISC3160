//function to fetch data from API
function fetchData() {
    // I found this data from https://data.cityofnewyork.us/Health/New-York-City-Leading-Causes-of-Death/jb7j-dtam

    fetch('https://data.cityofnewyork.us/resource/jb7j-dtam.json')
        .then(response => response.json())
        .then(json => displayData(json))
}
//function to display data back onto HTML by creating elements 
function displayData(json) {
    const main = document.querySelector('main');
    const table = document.createElement('TABLE');
    const headerRow = document.createElement('tr');

    const tHead1 = document.createElement('th');
    const tHead2 = document.createElement('th');
    const tHead3 = document.createElement('th');
    const tHead4 = document.createElement('th');

    tHead1.innerText = 'Year';
    tHead2.innerText = 'Leading Cause';
    tHead3.innerText = 'Sex';
    tHead4.innerText = 'Deaths';

    headerRow.append(tHead1, tHead2, tHead3, tHead4)

    table.appendChild(headerRow)
    //displaying data base off the API format used:
    //https://data.cityofnewyork.us/resource/jb7j-dtam.json
    json.forEach(data => {
        const row = document.createElement('tr');
        const popularName = document.createElement('td');
        popularName.innerText = data.year;

        const gender = document.createElement('td');
        gender.innerText = data.leading_cause;

        const totalNumber = document.createElement('td');
        totalNumber.innerText = data.sex;

        const rank = document.createElement('td');
        rank.innerText = data.deaths;

        row.append(popularName, gender, totalNumber, rank);
        table.appendChild(row);

    })
    //Add the table 
    main.appendChild(table);
}
// As soon as the DOM content is loaded run fetchdata function
document.addEventListener("DOMContentLoaded", function () {
    fetchData();
})
