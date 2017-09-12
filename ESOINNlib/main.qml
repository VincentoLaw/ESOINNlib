import QtQuick 2.7
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

        FileDialog{
            id: saveFileDialog
            title: "Please choose a image file to load"
            selectExisting:false
            nameFilters: [ "Text files (*.txt *.)" ]
            onAccepted: {
                dataEx.saveStructure = saveFileDialog.fileUrl.toString();
            }
        }
        FileDialog{
            id: openFileWithVector
            title: "Choose a file with input data in vectors"
            nameFilters: [ "Text files (*.txt *.)" ]
            onAccepted:{
                dataEx.loadVector = openFileWithVector.fileUrl.toString();
            }
        }

        FileDialog{
            id: loadFileDialog
            title: "Please choose a image file to load"
            nameFilters: [ "Text files (*.txt *.)" ]
            onAccepted: {
                dataEx.loadStructure = loadFileDialog.fileUrl.toString();
                settingsBar.currEsoinnData = dataEx.structureData.split(';');
                dataShowTimer.running = true;
            }
        }

        Rectangle{
            id: settingsBar
            height: 30
            color: "red"
            anchors.top: mainForm.top
            Button{
                id: loadImgButton
                text:"Load image"
                onClicked: {
                    fileDialog.open()
                }
            }
            Button {
                id:loadInputVector
                anchors.leftMargin: 10
                anchors.left: loadImgButton.right
                text: "Load input vector"
                onClicked: {
                    openFileWithVector.open();
                }
            }

            Button{
                id: showImgButton
                anchors.leftMargin: 10
                anchors.left: loadInputVector.right
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
            property var visualizeIter : 0;
            property var currEsoinnData : [];
            function learn(fromBegin){
                var beg_time = new Date();
                var arr = [nnComboBox.currentText, randomInput.checked, fullVisualize.checked, fromBegin, iterEdit.text, normalizeInput.checked, parseFloat(conAge.text), parseFloat(lambda.text), parseFloat(c1P.text), parseFloat(c2P.text)];
                dataEx.esoinnParams = arr;
                visualizeIter = 0;
                currEsoinnData = dataEx.structureData.split(';');
                var end_time = new Date();
                function time_ring(value, type){
                    if (value >= 0){
                        if (type != "ms")
                            return value;
                        else {
                            if (value < 10)
                                return "00" + value;
                            else if (value < 100) return "0" + value;
                            else return value;
                        }
                    }
                    if (type == "ms"){
                        value = 1000 + value;
                        if (value < 10)
                            return "00" + value;
                        else if (value < 100) return "0" + value;
                        else return value;
                    }
                    else return 60 + value;
                }

                var time_diff = time_ring(end_time.getMinutes() - beg_time.getMinutes(), "m") + "m. " + time_ring(end_time.getSeconds() - beg_time.getSeconds(), "s") + "." + time_ring(end_time.getMilliseconds() - beg_time.getMilliseconds(), "ms") + "s.";
                learnResultsText.text = dataEx.currentNNparams + ", Time elapsed: " + time_diff;
                //dataEx.saveMainVectors = "a";
                dataShowTimer.running = true;
            }

            Timer{
                id: dataShowTimer
                interval: 10;
                repeat: true;
                running: false;
                onTriggered: {
                    if (settingsBar.visualizeIter < settingsBar.currEsoinnData.length - 1){
                        canvas.loadStructure(settingsBar.currEsoinnData[settingsBar.visualizeIter]);
                        settingsBar.visualizeIter++;
                    }
                }
            }

            Button{
                id: learnBeginButton
                anchors.left: nnComboBox.right
                anchors.leftMargin: 10
                text:"LEARN FROM BEGIN"
                onClicked: {
                    settingsBar.learn("1");

                }
            }

            Button{
                id: learnButton
                anchors.left: learnBeginButton.right
                anchors.leftMargin: 10
                text:"LEARN ITERATIONS"
                onClicked: {
                    settingsBar.learn("0");
                }
            }

            Button{
                id: saveNNStructure
                anchors.left: learnButton.right
                anchors.leftMargin: 20
                text:"Save structure"
                onClicked: {
                    saveFileDialog.open();
                }
            }
            Button{
                id: loadNNStructure
                anchors.left: saveNNStructure.right
                anchors.leftMargin: 10
                text:"Load structure"
                onClicked: {
                    loadFileDialog.open();
                }
            }
        }

        Rectangle{
            id: settings2Bar
            height: 30
            color: "red"
            anchors.top: settingsBar.bottom
            anchors.leftMargin: 5
            Text{
                id: paramsText
                anchors.leftMargin: 10
                font.pointSize: 12
                text: "LEARN PARAMETRS:"
            }
            Text{
                id: iterText
                anchors.left: paramsText.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text: "Iterations:"
            }
            TextEdit{
                id: iterEdit
                color:"blue"
                anchors.left: iterText.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text:"1"
            }
            Text{
                id: text1
                anchors.left:iterEdit.right
                font.pointSize: 12
                anchors.leftMargin: 15
                text: "Max connection age:"
            }

            TextEdit{
                id: conAge
                color:"blue"
                anchors.left: text1.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text:"100"
            }
            Text{
                id: text2
                anchors.left:conAge.right
                font.pointSize: 12
                anchors.leftMargin: 15
                text:"Lambda:"
            }
            TextEdit{
                id: lambda
                color:"blue"
                anchors.left: text2.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text:"100"
            }
            Text{
                id: text3
                anchors.left:lambda.right
                anchors.leftMargin: 15
                font.pointSize: 12
                text:"c1:"
            }
            TextEdit{
                id: c1P
                color:"blue"
                anchors.left: text3.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text:"0.01"
            }
            Text{
                id: text4
                anchors.left:c1P.right
                anchors.leftMargin: 15
                font.pointSize: 12
                text:"c2:"
            }
            TextEdit{
                id: c2P
                color:"blue"
                anchors.left: text4.right
                anchors.leftMargin: 5
                font.pointSize: 12
                text:"1"
            }
        }
        Rectangle{
            id: settings3Bar
            height: 30
            anchors.top: settings2Bar.bottom
            CheckBox{
                id: randomInput
                text:"Randomize input data"
                checked: true
            }
            CheckBox{
                id: fullVisualize
                anchors.leftMargin: 5
                anchors.left: randomInput.right
                text:"Visualize every step"
                checked: false
            }
            CheckBox{
                id: normalizeInput
                anchors.leftMargin: 5
                anchors.left: fullVisualize.right
                text: "Normalize input"
                checked: false
            }
            CheckBox{
                id: showClustersIds
                anchors.leftMargin: 5
                anchors.left: normalizeInput.right
                text: "Show clusters ids"
                checked: false
            }

            Text{
                id: dimsText
                anchors.leftMargin: 5
                anchors.left: showClustersIds.right
                font.pointSize: 12
                text:"Visualize dimensions ids: "
            }
            TextEdit{
                id: fstDimId
                anchors.leftMargin: 5
                anchors.left: dimsText.right
                font.pointSize: 12
                color:"blue"
                text : "1"
            }
            Text{
                id: dimsDefisText
                anchors.leftMargin: 5
                anchors.left: fstDimId.right
                font.pointSize: 12
                text:"-"
            }
            TextEdit{
                id: secondDimId
                anchors.leftMargin: 5
                anchors.left: dimsDefisText.right
                font.pointSize: 12
                color:"blue"
                text: "2"
            }
        }
        Rectangle{
            id: settings4Bar
            height: 30
            anchors.top: settings3Bar.bottom
            Text{
                id: learnResultsText
            }
        }

        Image{
            id: imagePreview
            width: mainForm.width / 2
            anchors.top: settings4Bar.bottom
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
            anchors.top: settings4Bar.bottom
            anchors.bottom: mainForm.bottom
            anchors.left: imagePreview.right
            anchors.right: mainForm.right
            //anchors.fill: parent
            property var ctx : canvas.getContext("2d")

            onPaint:{
                ctx = canvas.getContext('2d');
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
            function loadStructure(data) {
                ctx.clearRect(0, 0, canvas.width, canvas.height);
                //data from esoin is in string in Person.name in format: "x y, x y, x y,"
                var arr = data.split('/');
                var showed_clusters = {};
                var cur_cluster_id = 0;

                var dimSize = dataEx.dimensionsCnt;
                var fstDim = parseInt(fstDimId.text);
                var secDim = parseInt(secondDimId.text);
                //console.log(arr)
                var min_x = 1000000, max_x = -1000000, min_y = 1000000, max_y = -1000000
                //finding the square, in that all data is lay
                for (var i = 0; i < arr.length; i++){
                    var numz = arr[i].split(' ');
                    numz[fstDim] = parseInt(numz[fstDim])
                    numz[secDim] = parseInt(numz[secDim])
                    if (numz[fstDim] > max_x)
                        max_x = numz[fstDim];
                    if (numz[fstDim] < min_x)
                        min_x = numz[fstDim];
                    if (numz[secDim] < min_y)
                        min_y = numz[secDim];
                    if (numz[secDim] > max_y)
                        max_y = numz[secDim];
                }
                //coefficents to transform data coordinates to see input in full window size
                var offset_x = -min_x;
                var offset_y = -min_y;
                if (max_x - min_x == 0)
                    max_x = min_x + 1;
                if (max_y - min_y == 0)
                    max_y = min_y + 1;
                var scale_x = (canvas.width - 100) / (max_x - min_x);
                var scale_y = (canvas.height - 100)/ (max_y - min_y);
                //console.log(min_x + ' ' + max_x + ' ' + min_y + ' ' + max_y)

                //this function resizes input coordinates fit to canvas size
                function newCoords(offset, scale, num){
                    return parseInt((parseInt(num) + offset) * scale + 50)
                }

                //draw points, that interpritates data
                for (var i = 0; i < arr.length; i++){
                      var nums = arr[i].split(' ');
                       //console.log(((parseInt(nums[0]) + offset_x) * scale_x) + ' ' + parseInt((parseInt(nums[1]) + offset_y)  * scale_y))
                      ctx.beginPath();
                      //ctx.fillStyle = "green"
                      //ctx.strokeStyle = "blue"
                      //if (nums[2] > 0)
                        //  ctx.fillStyle = "red"
                    function getCol(x){
                    if (x == 0) return 255;
                    var pow2 = Math.log(x+1) / Math.log(2);
                    var kolco = parseInt((x+1) % Math.pow(2,Math.floor(pow2)) * 2 - 1);
                    if (kolco == -1)
                       kolco = Math.pow(2,Math.ceil(pow2)) - 1;
                    return 256/Math.pow(2,Math.ceil(pow2))*kolco;
                    }
                    var color = getCol(nums[0]) / 255;
                    if (!nums[0] || nums[0] == -1){
                        color = 0;
                    }

                    var red = (nums[0] % 6 == 0 || nums[0] % 6 == 3 || nums[0] % 6 == 5) ? color : 0;
                    var green = (nums[0] % 6 == 0 || nums[0] % 6 == 4 || nums[0] % 6 == 2) ? color : 0;
                    var blue = (nums[0] % 6 == 5 || nums[0] % 6 == 4 || nums[0] % 6 == 1) ? color : 0;
                      ctx.fillStyle = Qt.rgba(red, green, blue, 1);
                    ctx.strokeStyle = Qt.rgba(red, green, blue, 1);
                      //console.log(colors)
                      //console.log(colors.length)

                    var temp_x = newCoords(offset_x, scale_x, nums[fstDim]);
                    var temp_y = newCoords(offset_y, scale_y, nums[secDim]);
                      ctx.arc( temp_x, temp_y, 3, 0, 2*Math.PI, false)
                      ctx.fill();
                      ctx.stroke();

                    //ctx.strokeStyle = "black"
                    //ctx.fillStyle = "black"
                    if (showClustersIds.checked && showed_clusters[nums[0]] != 1){
                        ctx.font = "24px fantasy";
                        //ctx.shadowColor = "white";
                        //ctx.shadowOffsetX = "1px";
                        //ctx.shadowOffsetX = "1px";
                        ctx.text(cur_cluster_id, temp_x, temp_y);

                        ctx.stroke();
                        showed_clusters[nums[0]] = 1;
                        cur_cluster_id++;
                    }
                    //console.log(nums[0] + "," + nums[1] + "," + nums[2] + "," + nums[3])
                    //console.log(dimSize);
                      //Draw connections
                      for (var j = 1 + dimSize; j < nums.length; j++){
                          if (nums[j] && nums[j] >= 0){
                              var xy = (arr[parseInt(nums[j])]).split(' ')
                              ctx.lineWidth = 1
                              ctx.strokeStyle = "black"
                              ctx.fillStyle = "black"
                              ctx.beginPath()
                              ctx.moveTo(newCoords(offset_x, scale_x, xy[fstDim]), newCoords(offset_y, scale_y, xy[secDim]))
                              ctx.lineTo(newCoords(offset_x, scale_x, nums[fstDim]), newCoords(offset_y, scale_y, nums[secDim]))
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
