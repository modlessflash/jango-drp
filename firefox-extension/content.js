function waitForElm(selector) { // https://stackoverflow.com/questions/5525071/how-to-wait-until-an-element-exists
    return new Promise(resolve => {
        if (document.querySelector(selector)) {
            return resolve(document.querySelector(selector));
        }

        const observer = new MutationObserver(mutations => {
            if (document.querySelector(selector)) {
                observer.disconnect();
                resolve(document.querySelector(selector));
            }
        });

        observer.observe(document.body, {
            childList: true,
            subtree: true
        });
    });
}

function once() {
  const artist = document.getElementById("player-artist").children[0].text;
  const title  = document.getElementById("player-song-title").children[0].text;
  const imgurl = document.getElementsByClassName("main-image")[0].src;

  const [minutes, seconds] = document.getElementById("player").children[0].children[0].children[1].children[1].children[0].textContent.split(":").map(Number);
  const time   = Date.now() - (60*minutes + seconds) * 1000 

  const btnstate = document.getElementById("player-play-button").children[0].dataset.icon;
  const playing = btnstate === "pause-circle" ? 1 : 0;

  fetch(`http://127.0.0.1:9294/jangodrp?artist=${encodeURIComponent(artist)}&title=${encodeURIComponent(title)}&imgurl=${encodeURIComponent(imgurl)}&time=${encodeURIComponent(time)}&playing=${encodeURIComponent(playing)}`);
}

function start() {
  once();
  setInterval(function() {
    once();
  }, 30000);
}

waitForElm("#player-artist").then((elm) => {
  start();
});