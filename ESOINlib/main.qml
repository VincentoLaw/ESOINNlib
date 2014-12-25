import QtQuick 2.4
import QtQuick.Window 2.2
//import People 1.0

Window {
    visible: true
    width:800
    height:800
    MainForm {
        color:"#FFFFFF"
        anchors.fill: parent
        //canvas is main control where i draw data
        Canvas{
            anchors.top: parent.top + 50
            anchors.fill: parent
            id: canvas
            onPaint: {
                var ctx = getContext("2d")
                //data from esoin is in string in Person.name in format: "x y, x y, x y,"
                var arr = Person.name.split(',');
                var min_x = 1000000, max_x = -1000000, min_y = 1000000, max_y = -1000000
                //finding the square, in that all data is lay
                for (var i = 0; i < arr.length; i++){
                    var numz = arr[i].split(' ');
                    numz[0] = parseInt(numz[0])
                    numz[1] = parseInt(numz[1])
                    if (numz[0] > max_x)
                        max_x = numz[0];
                    if (numz[0] < min_x)
                        min_x = numz[0];
                    if (numz[1] < min_y)
                        min_y = numz[1];
                    if (numz[1] > max_y)
                        max_y = numz[1];
                }
                //coefficents to transform data coordinates to see input in full window size
                var offset_x = -min_x + 5;
                var offset_y = -min_y + 5;
                var scale_x = (canvas.width - 20) / (max_x - min_x);
                var scale_y = (canvas.height - 20)/ (max_y - min_y);
                //draw points, that interpritates data
                for (var i = 0; i < arr.length; i++){
                      var nums = arr[i].split(' ');
                      ctx.beginPath();
                      ctx.fillStyle = "green"
                      ctx.strokeStyle = "blue"
                      ctx.arc(parseInt((parseInt(nums[0]) + offset_x) * scale_x), parseInt((parseInt(nums[1]) + offset_y)  * scale_y), 3, 0, 2*Math.PI, false)
                      ctx.fill();
                      ctx.stroke();
                }

                //Draw vertical coordinates line
                ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo(canvas.width / 2,0)
                ctx.lineTo(canvas.width / 2,canvas.height)
                ctx.stroke()
                //Draw horizontal coordinates line
                ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo(0,canvas.height / 2)
                ctx.lineTo(canvas.width,canvas.height / 2)
                ctx.stroke()


                //Draw horizontal scale on coordinate
                ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo(canvas.width - 10,canvas.height / 2 - 10)
                ctx.lineTo(canvas.width - 10,canvas.height / 2 + 10)
                ctx.stroke()
                ctx.beginPath();
                ctx.fillStyle = "black"
                ctx.strokeStyle = "black"
                ctx.font = "16px sans-serif";
                ctx.text(max_x, canvas.width - 30, canvas.height / 2 + 20);
                ctx.stroke();


                //Draw vertical scale on coordinate
                ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo(canvas.width / 2 - 10, 10)
                ctx.lineTo(canvas.width / 2 + 10, 10)
                ctx.stroke()
                ctx.beginPath();
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.font = "16px sans-serif";
                ctx.text(max_y, canvas.width / 2 - 10, 25);
                ctx.stroke();

            }
        }
    }
}
