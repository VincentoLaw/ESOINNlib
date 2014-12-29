import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

Window {
    visible: true
    width:1000
    height:800
    MainForm {
        id: mainForm
        color:"#FFFFFF"
        anchors.fill: parent
        //canvas is main control where i draw data
        FileDialog{
            id: fileDialog
            title: "Please choose a image file to load"
            nameFilters: [ "Image files (*.jpg *.png)" ]
            onAccepted: {
                  //console.log("You chose: " + fileDialog.fileUrls)
                imagePreview.source = fileDialog.fileUrl
                //console.log(imagePreview.data)
                var obj = imagePreview.data
                //for (x in obj) {
                //    console.log(x + " " + obj[x]);
                //}
                //console.log(Image.Ready)
                //console.log(imagePreview.data)
                //dataEx.structureData = imagePreview.data;

            }
        }

        Rectangle{
            id: settingsBar
            height: 50
            color: "blue"
            anchors.top: mainForm.top
            Button{
                id: loadImgButton
                text:"Load image"
                onClicked: {
                    fileDialog.open()
                }
            }
            Text{
                id: text1
                anchors.left:loadImgButton.right
                font.pointSize: 14
                anchors.leftMargin: 15
                text: "<b>Max connection age:</b>"
            }

            TextEdit{
                id: conAge
                anchors.left: text1.right
                anchors.leftMargin: 5
                font.pointSize: 14
                text:"20"
            }
            Text{
                id: text2
                anchors.left:conAge.right
                font.pointSize: 14
                anchors.leftMargin: 15
                text:"<b>Lambda:</b>"
            }
            TextEdit{
                id: lambda
                anchors.left: text2.right
                anchors.leftMargin: 5
                font.pointSize: 14
                text:"2"
            }
            Text{
                id: text3
                anchors.left:lambda.right
                anchors.leftMargin: 15
                font.pointSize: 14
                text:"<b>c1:</b>"
            }
            TextEdit{
                id: c1P
                anchors.left: text3.right
                anchors.leftMargin: 5
                font.pointSize: 14
                text:"1"
            }
            Text{
                id: text4
                anchors.left:c1P.right
                anchors.leftMargin: 15
                font.pointSize: 14
                text:"<b> c2: </b>"
            }
            TextEdit{
                id: c2P
                anchors.left: text4.right
                anchors.leftMargin: 5
                font.pointSize: 14
                text:"2"
            }
            Button{
                anchors.left: c2P.right
                anchors.leftMargin: 20
                text:"RUN"
                onClicked: {
                    var arr = [parseFloat(conAge.text), parseFloat(lambda.text), parseFloat(c1P.text), parseFloat(c2P.text)];
                    dataEx.esoinnParams = arr;
                    canvas.loadStructure();

                }
            }
        }

        Image{
            id: imagePreview
            width: mainForm.width / 2
            anchors.top: settingsBar.bottom
            anchors.bottom: mainForm.bottom
            anchors.left: mainForm.left
        }
        Colorize {
               anchors.fill: imagePreview
               source: imagePreview
               hue: 0.0
               saturation: 0
               lightness: 0
           }

        Canvas{
            id: canvas
            anchors.top: settingsBar.bottom
            anchors.bottom: mainForm.bottom
            anchors.left: imagePreview.right
            anchors.right: mainForm.right
            //anchors.fill: parent
            property var ctx : canvas.getContext("2d")

            MouseArea {
                id:mousearea
                hoverEnabled:true
                anchors.fill: parent
                onClicked:{
                    ctx.lineWidth = lineWidth
                    ctx.fillStyle = drawColor
                    ctx.fillRect(mousearea.mouseX, mousearea.mouseY, 2, 2);
                }
            }
            onPaint:{
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
            }
            function loadStructure() {
                ctx.clearRect(0,0, canvas.width, canvas.height)
                //data from esoin is in string in Person.name in format: "x y, x y, x y,"
                var arr = dataEx.structureData.split(',');
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
                canvas.requestPaint();
            }
        }
    }
}
