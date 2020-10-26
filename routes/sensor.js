const express = require("express");
const router = express.Router();
const sensorController = require("../controller/sensorController");
// api/sensor
router.post("/", sensorController.guardarData);
router.get("/", sensorController.obtenerData);

module.exports = router;
