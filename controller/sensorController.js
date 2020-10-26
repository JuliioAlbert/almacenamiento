const Sensor = require("../models/Sensor");

exports.guardarData = async (req, res) => {
  try {
    let sensor = new Sensor(req.body);
    await sensor.save();
    return res.status(200).json({
      ok: true,
      msj: "POST",
      sensor,
    });
  } catch (error) {
    return res.status(400).json({
      ok: false,
      msj: "Solo valores Boolean",
    });
  }
};

exports.obtenerData = async (req, res) => {
  let sensorData = await Sensor.find({});
  return res.json({
    sensorData,
  });
};
