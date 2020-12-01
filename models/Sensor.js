const mongoose = require('mongoose');

const SensorSchema = mongoose.Schema({
    estado: {
        type: Boolean,
        require: true,
    },
    temperatura: {
        type: Number,
        require: true
    },
    humedad: {
        type: Number,
        require: true,
    },
    fecha: {
        type: Date,
        default: Date.now
    }
});

module.exports = mongoose.model('Sensor', SensorSchema);