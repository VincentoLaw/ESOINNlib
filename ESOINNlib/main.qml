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
                dataEx.im = imagePreview.source

            }
        }

        Rectangle{
            id: settingsBar
            height: 50
            color: "red"
            anchors.top: mainForm.top
            Button{
                id: loadImgButton
                text:"Load image"
                onClicked: {
                    fileDialog.open()
                }
            }

            Button{
                id: showImgButton
                anchors.leftMargin: 10
                anchors.left: loadImgButton.right
                text:"Show pointed image"
                onClicked: {
                    dataEx.pointedImage = imagePreview.source
                    canvas.loadStructure();
                }
            }

            ComboBox{
                id: nnComboBox
                width:70
                currentIndex: 0
                anchors.left: showImgButton.right
                anchors.leftMargin: 10
                model:["ESOINN"]
            }

            Text{
                id: text1
                anchors.left:nnComboBox.right
                font.pointSize: 14
                anchors.leftMargin: 15
                text: "<b>Max connection age:</b>"
            }

            TextEdit{
                id: conAge
                anchors.left: text1.right
                anchors.leftMargin: 5
                font.pointSize: 14
                text:"100"
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
                text:"100"
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
                text:"0.001"
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
                text:"1"
            }
            Button{
                anchors.left: c2P.right
                anchors.leftMargin: 20
                text:"LEARN"
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

            onPaint:{
                //Draw vertical coordinates line
                /*ctx.lineWidth = 1
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
                ctx.stroke()*/
            }
            function loadStructure() {
                //data from esoin is in string in Person.name in format: "x y, x y, x y,"
                var arr = dataEx.structureData.split(',');
                //console.log(arr)
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
                var offset_x = -min_x;
                var offset_y = -min_y;
                if (max_x - min_x == 0)
                    max_x = min_x + 1;
                if (max_y - min_y == 0)
                    max_y = min_y + 1;
                var scale_x = (canvas.width - 20) / (max_x - min_x);
                var scale_y = (canvas.height - 20)/ (max_y - min_y);
                //console.log(min_x + ' ' + max_x + ' ' + min_y + ' ' + max_y)

                //this function resizes input coordinates fit to canvas size
                function newCoords(offset, scale, num){
                    return parseInt((parseInt(num) + offset) * scale + 10)
                }

                //draw points, that interpritates data
                for (var i = 0; i < arr.length; i++){
                      var nums = arr[i].split(' ');
                       //console.log(((parseInt(nums[0]) + offset_x) * scale_x) + ' ' + parseInt((parseInt(nums[1]) + offset_y)  * scale_y))
                      ctx.beginPath();
                      ctx.fillStyle = "green"
                      ctx.strokeStyle = "blue"
                      ctx.arc( newCoords(offset_x, scale_x, nums[0]), newCoords(offset_y, scale_y, nums[1]), 3, 0, 2*Math.PI, false)
                      ctx.fill();
                      ctx.stroke();

                      //Draw connections
                      for (var j = 2; j < nums.length; j++){
                          if (nums[j] && nums[j] >= 0){
                              var xy = (arr[parseInt(nums[j])]).split(' ')
                              ctx.lineWidth = 1
                              ctx.strokeStyle = "black"
                              ctx.fillStyle = "black"
                              ctx.beginPath()
                              ctx.moveTo(newCoords(offset_x, scale_x, xy[0]), newCoords(offset_y, scale_y, xy[1]))
                              ctx.lineTo(newCoords(offset_x, scale_x, nums[0]), newCoords(offset_y, scale_y, nums[1]))
                              //console.log(newCoords(offset_x, scale_x, xy[0]) + ' ' + newCoords(offset_y, scale_y, xy[1]))
                              //console.log(newCoords(offset_x, scale_x, nums[0])+ ' ' + newCoords(offset_y, scale_y, nums[1]))
                              ctx.stroke()
                          }
                      }
                }
                //console.log(offset_x + ' ' + offset_y + ' ' + scale_x + ' ' + scale_y)
                //Draw vertical coordinates line
                /*ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo( parseInt((offset_x) * scale_x) + 10,0)
                ctx.lineTo(parseInt((offset_x) * scale_x) + 10,canvas.height)
                ctx.stroke()
                //Draw horizontal coordinates line
                ctx.lineWidth = 1
                ctx.strokeStyle = "black"
                ctx.fillStyle = "black"
                ctx.beginPath()
                ctx.moveTo(0,parseInt((offset_y) * scale_y) + 10)
                ctx.lineTo(canvas.width,parseInt((offset_y) * scale_y) + 10)
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
                ctx.stroke();*/
                canvas.requestPaint();
            }
        }
    }
}
