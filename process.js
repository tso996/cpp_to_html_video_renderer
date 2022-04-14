
var Module = {
    onRuntimeInitialized: function() {
        videoWidth = 640
        videoHeight = 480
        let cnv = document.createElement("canvas");
        cnv.width = videoWidth;
        cnv.height = videoHeight;
        let tempCanvasCtx = cnv.getContext("2d");
        let stopVideo = false;
        let starter = true
        fps = 60
        let et = document.createElement("div");
        let etParent = document.querySelector(".jumbotron");
        etParent.appendChild(et);


        let video = document.getElementById("videoInput"); // video is the id of video tag
        let init = async function () {
            const stream = await navigator.mediaDevices.getUserMedia({
                video: {
                width: videoWidth,
                height: videoHeight,
                facingMode: "environment",
                },
            });
            video.srcObject = stream;
            video.setAttribute("playsinline", "true");
            await video.play();
            };


        let captureVideoImage = function () {
                tempCanvasCtx.drawImage(video, 0, 0);
                const imageData = tempCanvasCtx.getImageData(0, 0, videoWidth, videoHeight);
                return imageData;
            };

        let looper = async function (fps) {
                const initialisations = await init();
                var instance = new Module.MyClass();
                // instance.incrementX();
                // instance.x; // 11
                // instance.x = 20; // 20
                // Module.MyClass.getStringFromInstance(instance); // "hello"
                // instance.delete();
        
                ///initialization is over
                //===========================================
                (function loop() {
                if(starter){
                let begin = Date.now();
                try {
                    console.log("in loop!")
                    const imageFrameData = captureVideoImage();
                    const imageFrameDataSize = 4 * imageFrameData.width * imageFrameData.height;
                    let imgPointer = Module._malloc(imageFrameDataSize);
                    Module.HEAPU8.set(imageFrameData.data, imgPointer);
                    //run main cpp function here
                    console.log("before process!")
                    let executionTime = instance.runMainProcess(imgPointer,imageFrameDataSize);
                    console.log("after process!")
                    et.innerHTML = executionTime+"ms";
                    //==============      
                    Module._free(imgPointer);






                } catch (e) {
                    console.log("error is: ", e);
                }
                //====================================
                if (!stopVideo) {
                    let delay = 1000 / fps - (Date.now() - begin);
                    setTimeout(loop, delay);
                }
                }
                // animationLoopId = window.requestAnimationFrame(loop);
                })();
            };
            setTimeout(function() {
                looper(fps);
                }, 1000);
            
                //press esc to stop the video process
            let a = document.addEventListener("keydown", function (e) {
                if (e.key === "Escape") {
                stop(e);
                }
            });
        
            //==================
            function stop(e) {
                starter = false;
                console.log("video stopped!");
                var stream = video.srcObject;
                var tracks = stream.getTracks();
        
                for (var i = 0; i < tracks.length; i++) {
                var track = tracks[i];
                track.stop();
                }
                video.srcObject = null;
                stopVideo = true;
            }
        }
    }