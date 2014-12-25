import QtQuick 2.3

Canvas{
    anchors.top: parent.top + 50
    anchors.fill: parent
    // handler to override for drawing
    onPaint: {
        // get context to draw with
        var ctx = getContext("2d")
        ctx.lineWidth = 10
        ctx.strokeStyle = "blue"
        ctx.fillStyle = "steelblue"
        ctx.beginPath()
        ctx.moveTo(10,10)
        ctx.lineTo(50,50)
        ctx.stroke()
        ctx.beginPath();
          ctx.fillStyle = "orange"
          ctx.strokeStyle = "red"
          ctx.moveTo(width/2+60, height/2);
          ctx.arc(width/2, height/2, 60, 0, 2*Math.PI, true)
          ctx.fill();
          ctx.stroke();
    }
}

