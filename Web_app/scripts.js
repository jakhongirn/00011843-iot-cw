
const firebaseConfig = {
  apiKey: "AIzaSyDXXxFL03802VQC9onjWHIhcq1BZNwgxKM",
  authDomain: "iot-pro-a1acb.firebaseapp.com",
  databaseURL: "https://iot-pro-a1acb-default-rtdb.firebaseio.com",
  projectId: "iot-pro-a1acb",
  storageBucket: "iot-pro-a1acb.appspot.com",
  messagingSenderId: "341808269201",
  appId: "1:341808269201:web:851aa561d41f27932a7c30",
  measurementId: "G-TR68WWTL8W"
};


// Initialize Firebase

//const app = initializeApp(firebaseConfig);

//const analytics = getAnalytics(app);
firebase.initializeApp(firebaseConfig);

  // getting reference to the database
  var database = firebase.database();

  //getting reference to the data we want
  var dataRef1 = database.ref('humid');
  var dataRef2 = database.ref('temp');
  var dataRef3 = database.ref('FAN');

  //fetch the data
  dataRef1.on('value', function(getdata1){
    var humi = getdata1.val();
    document.getElementById('humidity').innerHTML = humi + "%";
  })

   dataRef2.on('value', function(getdata2){
    var temp = getdata2.val();
    document.getElementById('temperature').innerHTML = temp + "&#8451;";
  })



var index=0;
var btn=document.getElementById("FAN");

function press() {
index++;
if (index%2==1) {
database.ref('FAN').set("1");
document.getElementById('FAN').innerHTML="turn off";
}
else {
database.ref('FAN').set("0");
document.getElementById('FAN').innerHTML="turn on";
}
}