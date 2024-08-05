window.onload = refreshSession;
function refreshSession() {
  if (window.location.href == sessionStorage.getItem("origin")) {
    sessionStorage.clear();
  }
  sessionStorage.setItem("origin", window.location.href);

  setTimeout(onLoad, 30);
}

window.onscroll = function() {scrollFunction()};

function scrollFunction() {
  if (document.body.scrollTop > 20 || document.documentElement.scrollTop > 20) {
    document.getElementById("navbar").style.top = "0";
  } else {
    document.getElementById("navbar").style.top = "-50px";
  }
}