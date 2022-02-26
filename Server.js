var express = require("express");
var app = express();
app.use(express.static("public"));
app.set("view engine", "ejs");
app.set("views", "./views");

var server = require("http").Server(app);
var io = require("socket.io")(server);
const PORT = process.env.PORT || 3000;
server.listen(PORT);

io.on("connection", function(socket) {
    console.log("COnnection");
});

app.get("/", function(req, res) {
    res.render("Home");
});