const express = require('express')
const app = express()
const port = 3000
const rateLimit = require("express-rate-limit");
const bodyParser = require('body-parser');

const measurementLimiter = rateLimit({
  windowMs: 1000, // time window
  max: 2, // start blocking after 5 requests
  message: "Too many measurements this IP"
});

app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

const setMeasurement = async (req, res, next) => {
  console.log("CALLED")
  res.send('Got a POST request')
  console.log(req.body.capacity)
};

app.post('/measurement/sensor_1', measurementLimiter, setMeasurement)


app.listen(port, () => console.log(`Example app listening at http://localhostnode app.js:${port}`))