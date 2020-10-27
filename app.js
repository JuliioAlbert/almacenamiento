const express = require("express");
const conectarDB = require("./config/db");
const cors = require("cors");
const bodyParser = require('body-parser');
//crear el Servidor
const app = express();

//Conectar a la base de datos

conectarDB();

//Habilitar Cors
app.use(cors());

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
