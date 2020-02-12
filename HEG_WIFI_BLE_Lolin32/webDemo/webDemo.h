const char event_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="webDemoCSS.css">
<script src="HEGwebAPI.js"></script>
</head>
<body>
  <title>HEG Interface</title>
  <div class="header">
      <h1>HEG ALPHA Ver 0.0.3</h1>
  </div>
  
  <div id="main_body"></div>



<script>
//Rough Draft scripts. Generalize the onData, replayCSV, and handleEventData calls

var s = new HEGwebAPI('',false);
var g = new graphJS(1000,[255,100,80,1],1,[1400,600], "main_body", "g", false);
var c = new circleJS(); //Default animation initialized first
var v = null;
var a = null;
var h = null;

var useGraph = true;
var useCanvas = true;
var useVideo = false;
var useAudio = false;
var useHills = false;

// Modal Code
var switchHTML = '<label class="switch"><input type="checkbox" id="togBtn"><div class="startslider round"></div></label>';

var tabHTML = '<div id="tabContainer"> \
  <button class="tablink" id="modal_opener">Data</button> \
  <button class="tablink" id="modal_opener2">Graph</button> \
  <button class="tablink" id="modal_opener3">Feedback</button> \
  </div> \
  <div class="modal" style="display: none"> \
  <div class="overlay"></div> \
    <div class="modal_content"> \
      <h2>Data Options</h2> \
      <div id="dataBox"></div> \
      <button title="Close" class="close_modal"> \
          <i class="fas fa-times"></i> \
      </button> \
    </div> \
  </div> \
  <div class="modal2" style="display: none"> \
  <div class="overlay2"></div> \
    <div id="graphBox" class="modal_content2"> \
      <h2>Graph Options</h2> \
      <button title="Close" class="close_modal2"> \
          <i class="fas fa-times"></i> \
      </button> \
    </div> \
  </div> \
  <div class="modal3" style="display: none"> \
  <div class="overlay3"></div> \
    <div id = "visualBox" class="modal_content3"> \
      <h2>Feedback Options</h2> \
      <button title="Close" class="close_modal3"> \
          <i class="fas fa-times"></i> \
      </button> \
    </div> \
  </div>';


HEGwebAPI.appendFragment(switchHTML, "main_body");
HEGwebAPI.appendFragment(tabHTML, "main_body");

var btn = document.getElementById('modal_opener');
var btn2 = document.getElementById('modal_opener2');
var btn3 = document.getElementById('modal_opener3');

var modal = document.querySelector('.modal');
var modal2 = document.querySelector('.modal2')
var modal3 = document.querySelector('.modal3')

function attachModalListeners(modalElm) {
  modalElm.querySelector('.close_modal').addEventListener('click', toggleModal);
  modalElm.querySelector('.overlay').addEventListener('click', toggleModal);
}

function detachModalListeners(modalElm) {
  modalElm.querySelector('.close_modal').removeEventListener('click', toggleModal);
  modalElm.querySelector('.overlay').removeEventListener('click', toggleModal);
}

function toggleModal() {
  var currentState = modal.style.display;

  // If modal is visible, hide it. Else, display it.
  if (currentState === 'none') {
    modal.style.display = 'block';
    attachModalListeners(modal);
  } else {
    modal.style.display = 'none';
    detachModalListeners(modal);  
  }
}

btn.addEventListener('click', toggleModal);

function attachModalListeners2(modalElm) {
  modalElm.querySelector('.close_modal2').addEventListener('click', toggleModal2);
  modalElm.querySelector('.overlay2').addEventListener('click', toggleModal2);
}

function detachModalListeners2(modalElm) {
  modalElm.querySelector('.close_modal2').removeEventListener('click', toggleModal2);
  modalElm.querySelector('.overlay2').removeEventListener('click', toggleModal2);
}

function toggleModal2() {
  var currentState = modal2.style.display;

  // If modal is visible, hide it. Else, display it.
  if (currentState === 'none') {
    modal2.style.display = 'block';
    attachModalListeners2(modal2);
  } else {
    modal2.style.display = 'none';
    detachModalListeners2(modal2);  
  }
}

btn2.addEventListener('click', toggleModal2);

function attachModalListeners3(modalElm) {
  modalElm.querySelector('.close_modal3').addEventListener('click', toggleModal3);
  modalElm.querySelector('.overlay3').addEventListener('click', toggleModal3);
}

function detachModalListeners3(modalElm) {
  modalElm.querySelector('.close_modal3').removeEventListener('click', toggleModal3);
  modalElm.querySelector('.overlay3').removeEventListener('click', toggleModal3);
}

function toggleModal3() {
  var currentState = modal3.style.display;

  // If modal is visible, hide it. Else, display it.
  if (currentState === 'none') {
    modal3.style.display = 'block';
    attachModalListeners3(modal3);
  } else {
    modal3.style.display = 'none';
    detachModalListeners3(modal3);  
  }
}

btn3.addEventListener('click', toggleModal3);

function toggleHEG(switchElement) {
  if (switchElement.checked) {
    document.getElementById('startbutton').click();
  } else {
    document.getElementById('stopbutton').click();
  }
}
document.getElementById("togBtn").onchange = function(){toggleHEG(document.getElementById("togBtn"))};
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

s.createUI("dataBox");
g.createUI("graphBox")

var modeHTML = '<div class="menudiv" id="menudiv"> \
  Modes:<br> \
  <button class="button cvbutton" id="canvasmode">Canvas</button><button class="button vdbutton" id="videomode">Video</button><button class="button aubutton" id="audiomode">Audio</button><br> \
  <button class="button lfbutton" id="hillmode">Hill Climb</button> \
</div>';

HEGwebAPI.appendFragment(modeHTML,"visualBox");

function deInitMode(){
  if(useVideo == true){
    var thisNode = document.getElementById(v.vidapiId);
    thisNode.parentNode.parentNode.removeChild(thisNode.parentNode);
    thisNode = document.getElementById(v.vidContainerId);    
    thisNode.parentNode.parentNode.removeChild(thisNode.parentNode);
    v.deInit();
    useVideo = false;
    v = null;
  }
  if(useAudio == true){
    a.stopAudio();
    a.endAudio(a);
    var thisNode = document.getElementById(a.audioId);
    thisNode.parentNode.parentNode.removeChild(thisNode.parentNode);
    thisNode = document.getElementById(a.audmenuId);
    thisNode.parentNode.parentNode.removeChild(thisNode.parentNode);
    useAudio = false;
    a = null;
  }
  if(useCanvas == true){
    c.deInit();
    c.c.parentNode.parentNode.parentNode.removeChild(c.c.parentNode.parentNode);
    useCanvas = false;
    c = null;
  }
  if(useHills == true){
    h.deInit();
    h.c.parentNode.parentNode.parentNode.removeChild(h.c.parentNode.parentNode);
    h.menu.parentNode.removeChild(h.menu);
    useHills = false;
    h = null;
  }
}

document.getElementById("canvasmode").onclick = function() {
  if(useCanvas == false){
    deInitMode();
    c = new circleJS();
    useCanvas = true;
  }
}

document.getElementById("videomode").onclick = function() {
  if(useVideo == false){
    deInitMode();
    v = new videoJS();
    useVideo = true
  }
}

document.getElementById("audiomode").onclick = function() {
  if(useAudio == false){
    deInitMode();
    a = new audioJS();
    useAudio = true; 
  }
}

document.getElementById("hillmode").onclick = function() {
  if(useHills == false){
    deInitMode();
    h = new hillJS();
    useHills = true;
  }
}

g.xoffsetSlider.onchange = () => {
   if(g.xoffsetSlider.value > s.scoreArr.length) {
     g.xoffsetSlider.value = s.scoreArr.length - 1;
   }
   g.offset = g.xoffsetSlider.value;
   
   if(s.scoreArr.length > g.graphY1.length){ //more data than graph size, so just grab a slice of the graph
    var endIndex = s.scoreArr.length - g.offset - 1;
    g.graphY1 = s.scoreArr.slice(endIndex - g.graphY1.length, endIndex); // FIX 
    g.graphY2 = s.ratio.slice(endIndex -g.graphY2.length, endIndex);
   }
   else if (s.scoreArr.length < g.graphY1.length) { //less data than graph size, generate zeroes with data from 0 to offset
    var scoreslice = s.scoreArr.slice(0,s.scoreArr.length - 1 - g.offset);
    var ratioslice = s.ratio.slice(0,s.ratio.length - 1 - g.offset);
    if(g.graphY1.length == scoreslice){
      g.graphY1 = scoreslice;
      g.graphY2 = ratioslice;
    }
    else{
      g.graphY1 = [...Array(g.VERTEX_LENGTH - scoreslice.length).fill(0), ...scoreslice];
      g.graphY2 = [...Array(g.VERTEX_LENGTH - ratioslice.length).fill(0), ...ratioslice];
    }
   }
}

g.xscaleSlider.onchange = () => {
  len = g.graphY1.length;
  if(g.xscaleSlider.value < len) { // Remove from front.
    for(var i = 0; i < len - g.xscaleSlider.value; i++){
      g.graphY1.shift();
      g.graphY2.shift();
    }
  }
  if(g.xscaleSlider.value > len) { // Add to front
    for(var i = 0; i < g.xscaleSlider.value - len; i++){
      if(i+len+g.offset <= s.scoreArr.length){
        g.graphY1.unshift(s.scoreArr[s.scoreArr.length - ((len+i) + g.offset)]);
        g.graphY2.unshift(s.ratio[s.ratio.length - ((len+i) + g.offset)]);
      } 
      else{
        g.graphY1.unshift(0);
        g.graphY2.unshift(0);
      }
    }
  }
  g.VERTEX_LENGTH = g.graphY1.length;
}

document.getElementById("xscalebutton").onclick = () => {
  var len = g.graphY1.length;
  g.xscaleSlider.value = 1000;
  if(g.xscaleSlider.value < len) { // Remove from front.
    for(var i = 0; i < len - g.xscaleSlider.value; i++){
      g.graphY1.shift();
      g.graphY2.shift();
    }
  }
  if(g.xscaleSlider.value > len) { // Add to front
    for(var i = 0; i < g.xscaleSlider.value - len; i++){
      if(g.xscaleSlider.value < s.scoreArr.length){
        g.graphY1.unshift(s.scoreArr[s.scoreArr.length - 1 - ((g.graphY1.length+i) + g.offset)]);
        g.graphY2.unshift(s.ratio[s.ratio.length - 1 - ((g.graphY2.length+i) + g.offset)]);
      } 
      else{
        g.graphY1.unshift(0);
        g.graphY2.unshift(0);
      }
    }
  }
  g.VERTEX_LENGTH = g.xscaleSlider.value;
}

//document.getElementById("resetButton").onclick = () => {
  //s.resetVars();
  //g.graphY1 = [...Array(g.VERTEX_LENGTH).fill(0)]
//}

s.replayCSV = function() { //REDO IN GENERALIZED FORMAT
  if(this.csvIndex < 2){
    if(useVideo == true){
      v.playRate = 1;
      v.alpha = 0;
    }
    if(useCanvas == true){
      c.angle = 1.57;
    }
    if(this.startTime == 0) { this.startTime = this.csvDat[this.csvIndex][0]}
    this.us.push(parseInt(this.csvDat[this.csvIndex][0]));
    this.red.push(parseInt(this.csvDat[this.csvIndex][1]));
    this.ir.push(parseInt(this.csvDat[this.csvIndex][2]));
    this.ratio.push(parseFloat(this.csvDat[this.csvIndex][3]));
    this.ambient.push(parseInt(this.csvDat[this.csvIndex][4]));
    this.velAvg.push(parseFloat(this.csvDat[this.csvIndex][5]));
    this.accelAvg.push(parseFloat(this.csvDat[this.csvIndex][6]));
  }
  this.csvIndex++;
  if(this.csvIndex < this.csvDat.length - 1){
    if(this.startTime == 0) { this.startTime = this.csvDat[this.csvIndex][0]}
    this.us.push(parseInt(this.csvDat[this.csvIndex][0]));
    this.red.push(parseInt(this.csvDat[this.csvIndex][1]));
    this.ir.push(parseInt(this.csvDat[this.csvIndex][2]));
    this.ratio.push(parseFloat(this.csvDat[this.csvIndex][3]));
    this.ambient.push(parseInt(this.csvDat[this.csvIndex][4]));
    this.velAvg.push(parseFloat(this.csvDat[this.csvIndex][5]));
    this.accelAvg.push(parseFloat(this.csvDat[this.csvIndex][6]));
    parent.postMessage( this.ratio[this.ratio.length-1], "*");
    g.us = this.us[this.us.length - 1] - this.startTime;
    if(this.us.length >= 2){
      if(this.ratio.length > 40){
        this.smaScore(this.ratio);
        var score = this.smaSlope*this.sensitivity.value*0.01;
        if(useCanvas == true){
          c.onData(score);
        }
        if (useVideo == true) {
          v.onData(score);
        }
        if(useAudio == true) {
          a.onData(score);
        }
        if(useHills == true) {
          h.onData(score);
        }
        this.scoreArr.push(this.scoreArr[this.scoreArr.length - 1] + score);
        g.ratio = this.slowSMA;
        g.score = this.scoreArr[this.scoreArr.length - 1];
        g.graphY1.shift();
        g.graphY1.push(this.scoreArr[this.scoreArr.length - 1 - g.offset]);
        g.graphY2.shift();
        g.graphY2.push(this.slowSMAarr[this.slowSMAarr.length - 1 - g.offset]);
      }
      else {
        //this.smaSlope = this.scoreArr[this.scoreArr.length - 1];
        //g.graphY1.shift();
        //g.graphY1.push(this.smaSlope);
        //this.scoreArr.push(this.smaSlope);
      }
      this.updateTable();
    }
  }
  else {
    this.replay = false;
    this.csvDat = [];
    this.csvIndex = 0;
  }
  if(g.xoffsetSlider.max < this.scoreArr.length){
    if(this.scoreArr.length % 20 == 0) { //only update every 20 samples
      g.xoffsetSlider.max = this.scoreArr.length - 3;
    }
  }
  setTimeout(() => {this.replayCSV();},(this.us[this.csvIndex]-this.us[this.csvIndex-1])*0.001); //Call until end of index.
}

var handleEventData = (e) => { //REDO THESE ONES IN A GENERALIZED WAY
  console.log("event", e.data);
  if(document.getElementById("heg").innerHTML != e.data){  //on new output
    document.getElementById("heg").innerHTML = e.data; // Use stored variable for this instead to save memory
    if(e.data.includes("|")) {
      var dataArray = e.data.split("|");
      if(parseFloat(dataArray[3]) > 0) { // Skip values not within a certain error.
        if(s.startTime == 0) { s.startTime = parseInt(dataArray[0])}
        s.us.push(parseInt(dataArray[0]));
        s.red.push(parseInt(dataArray[1]));
        s.ir.push(parseInt(dataArray[2]));
        s.ratio.push(parseFloat(dataArray[3]));
        s.ambient.push(parseInt(dataArray[4]));
        s.velAvg.push(parseFloat(dataArray[5]));
        s.accelAvg.push(parseFloat(dataArray[6]));
        parent.postMessage( s.ratio[s.ratio.length-1], "*");
        g.us = s.us[s.us.length - 1] - s.startTime;
        //handle new data
        if(s.ratio.length-1 > 40){
          s.smaScore(s.ratio);
          var score = s.smaSlope*s.sensitivity.value*0.01;
          if(useCanvas == true){
            c.onData(score);
          }
          if (useVideo == true) {
            v.onData(score);
          }
          if(useAudio == true) {
            a.onData(score);
          }
          if(useHills == true) {
            h.onData(score);
          }
          s.scoreArr.push(s.scoreArr[s.scoreArr.length - 1] + score);
          g.ratio = s.slowSMA;
          g.score = s.scoreArr[s.scoreArr.length - 1];
          g.graphY1.shift();
          g.graphY1.push(s.scoreArr[s.scoreArr.length - 1 - g.offset]);
          g.graphY2.shift();
          g.graphY2.push(s.slowSMAarr[s.slowSMAarr.length - 1 - g.offset]);
        }
        s.updateTable(); 
      } 
    }
  }
  //handle if data not changed
  else if (s.replay == false) {
    //s.smaSlope = s.scoreArr[s.scoreArr.length - 1];
    //g.graphY1.shift();
    //g.graphY1.push(s.scoreArr[s.scoreArr.length - 1 - g.offset]);
    //s.scoreArr.push(s.smaSlope);
  }
  if(g.xoffsetSlider.max < s.scoreArr.length){
    if(s.scoreArr.length % 20 == 0) { 
      g.xoffsetSlider.max = s.scoreArr.length - 3; //Need 2 vertices minimum
    }
  }
}

s.handleData = (e) => { //Set event data handler for this page.
  handleEventData(e);
}
</script>
</body>
</html>
)=====";