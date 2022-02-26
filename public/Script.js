var socket = io("https://http://localhost:3000")

$(document).ready(function() {
    $("#button").click(function() {
        socket.emit("cilent-send-data");
    })
});