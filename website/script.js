// audio setup
const audio = new Audio('music.mp3');
function play_music() {
    audio.play();
    audio.addEventListener("ended",function(){this.play()});
}

// navigation bar and assorted pages
const navis = ["nav1", "nav2", "nav3"];
const pages = ["home", "educ", "cont"]; 

function show(shown, id_list) {
    for (var i = 0; i < id_list.length; i++) {
        var el = document.getElementById(id_list[i]);
        if (shown == id_list[i]) {el.classList.add("active");}
        else {el.classList.remove("active");}
    }
}

function shift_pages(nav, page) {
    show(nav, navis);
    show(page, pages);
}
