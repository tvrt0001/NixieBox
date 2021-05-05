
function particleEffect () {
  var distance = Math.sqrt(a * a + b * b);
  if (distance < radius * 70) {
    this.accX = (this.x - mouse.x) / 100;
    this.accY = (this.y - mouse.y) / 100;
    this.vx += this.accX;
    this.vy += this.accY;
  }
}

function onMouseMove(e) {
  mouse.x = e.clientX;
  mouse.y = e.clientY;
}

function onTouchMove(e) {
  if (e.touches.length > 0) {
    mouse.x = e.touches[0].clientX;
    mouse.y = e.touches[0].clientY;
  }
}

function onTouchEnd(e) {
  mouse.x = -9999;
  mouse.y = -9999;
}

function initScene() {
  ww = canvas.width = window.innerWidth;
  wh = canvas.height = window.innerHeight;

  ctx.clearRect(0, 0, canvas.width, canvas.height);

  ctx.font = "bold " + ww / 10 + "px sans-serif";
  ctx.textAlign = "center";
  ctx.fillText(copy.value, ww / 2, wh / 2);

  var data = ctx.getImageData(0, 0, ww, wh).data;
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.globalCompositeOperation = "screen";

  particles = [];
  for (var i = 0; i < ww; i += Math.round(ww / 150)) {
    for (var j = 0; j < wh; j += Math.round(ww / 150)) {
      if (data[(i + j * ww) * 4 + 3] > 150) {
        particles.push(new Particle(i, j));
      }
    }
  }
  amount = particles.length;
}

function onMouseClick() {
  radius++;
  if (radius === 5) {
    radius = 0;
  }
}

function render(a) {
  requestAnimationFrame(render);
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  for (var i = 0; i < amount; i++) {
    particles[i].render();
  }
}


copy.addEventListener("keyup", initScene);
window.addEventListener("resize", initScene);
window.addEventListener("mousemove", onMouseMove);
window.addEventListener("touchmove", onTouchMove);
window.addEventListener("click", onMouseClick);
window.addEventListener("touchend", onTouchEnd);
initScene();
requestAnimationFrame(render);



/* NOT SURE  

attachAnimation: function(payload) {
    /*
            <section class="container">
            <h1>
                <span class="title">This is</span>
                <span class="title">a long</span>
                <span class="title">long title</span>
            </h1>
            
            <div class="button">restart</div>
            </section>
    */
}

*/

