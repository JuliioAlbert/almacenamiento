const express = require("express");
const conectarDB = require("./config/db");
require("cors");
const bodyParser = require('body-parser');
//crear el Servidor
const app = express();

//Acceso CORS
app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*"); // update to match the domain you will make the request from
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  res.header("Access-Control-Allow-Methods", "POST, GET, PUT, DELETE, OPTIONS")
  next();
});

//Conectar a la base de datos
conectarDB();


//Habilitar express.json
app.use(bodyParser.urlencoded({ extended: false }))
app.use(bodyParser.json())

//Puerto de la app
const port = process.env.PORT || 4000;

//importar Rutas
app.use("/api/sensor", require("./routes/sensor"));

//Arrancar la app
app.listen(port, () => {
  console.log(`El Servidor esta funcionando en el puerto ${port}`);
});
