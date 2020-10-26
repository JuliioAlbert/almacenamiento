const mongoose = require('mongoose');

const SensorSchema = mongoose.Schema({
    estado: {
        type: Boolean,
        require: true,
    },
});

module.exports = mongoose.model('Sensor', SensorSchema);