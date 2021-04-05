const mongoose = require('mongoose');

mongoose.connect('mongodb://iot_db:iot_db@localhost:27017/iot_database');

const db = mongoose.connection;

db.on('error', () => {
    console.log(`Connection Failed!`);
});

db.once('open', () => {
    console.log(`Connected!`);
});

const iot_device = mongoose.Schema({
    mac_address : 'String',
    device_date : 'Date',
    count : 'Number'
});

const Device = mongoose.model('Schema', iot_device);

const device_01 = new Device({ mac_address : "aa:bb:cc:dd:ee:ff", device_date : Date(), count:  0 });

device_01.save((err, data) => {
    if(err) {
        console.log(err);
    }
    else {
        console.log(`Saved!`);
    }
});

Device.find((err, devices) => {
    console.log(` --- Read all --- `);
    if(err) {
        console.log(err);
    }
    else {
        console.log(devices);
    }
});

// Device.findById({mac_address : "aa:bb:cc:dd:ee:ff"}, (err, device) => {
//     console.log(` --- Update (PUT) ---`);
//     if(err) {
//         console.log(err);
//     }
//     else {
//         device.count = 25;
//         device.save((err, modified_device) => {
//             if(err) {
//                 console.log(err);
//             }
//             else {
//                 console.log(modified_device);
//             }
//         });
//     }
// });

// Device.remove({mac_address : "aa:bb:cc:dd:ee:ff"}, (err, result) => {
//     console.log(` --- Delete --- `);
//     if(err) { 
//         console.log(err);
//     }
// });
