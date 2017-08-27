$(document).ready(function() {
  var prompt =
  [
    {
      "name" : "TurboSh",
      "prompt" : "##<span class=\"green\">user</span>:<span class=\"blue\">~/actual/path</span> $"
    },
    {
      "name" : "Bash Style",
      "prompt" : "<span class=\"green\">user@hostname</span><span class=\"blue\">:~/actual/path</span>$ "
    },
    {
      "name" : "TCSH Style",
      "prompt" : "<span class=\"underline\">hostname</span>:<span class=\"white\">~/actual/path</span>&gt;"
    },
    {
      "name" : "Minimalist",
      "prompt" : "user) "
    },
    {
      "name" : "Tomato Ketchup",
      "prompt" : "<span class=\"green\">user</span>#<span class=\"red\">~/actual/path</span> $"
    },
    {
      "name" : "Big Mac",
      "prompt" : "[<span class=\"purple\">arthur</span>@<span class=\"red\">arthur-pc</span> <span class=\"green\">~/actual/path</span>]$ "
    },
    {
	"name" : "Oh My Zsh",
	"prompt" : "<span class=\"green\">→</span> <span class=\"light-blue\">path</span> <span class=\"blue\">\
git:(</span><span class=\"red\">branch</span><span class=\"blue\">)</span>"
    }
  ];
  var selected = -1;

  function getSelected() {
    var xhr = getXMLHttpRequest();
    xhr.onreadystatechange = function() {
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
          selected = parseInt(xhr.responseText);
          displayPrompt();
        }
      };
    if (port) {
      xhr.open("GET", "http://localhost:" + port + "/exec?arg=get_prompt_sel", true);
      xhr.send(null);
    } else {
      alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
    }
  }

  function updatePrompt() {
    var xhr = getXMLHttpRequest();
    var idSelected = this.id.substr(6);
    xhr.onreadystatechange = function() {
      if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
          getSelected();
        }
      };
    if (port) {
      xhr.open("GET", "http://localhost:" + port + "/exec?arg=update_prompt_sel&val=" + idSelected, true);
      xhr.send(null);
    } else {
      alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
    }
  }

  function displayPrompt() {
    var add = document.getElementById("promptAddList");
    add.innerHTML = "";
    var i = 0;
    while (i < prompt.length)
    {
      var div = document.createElement("div");
      div.className = "prompt-list";

      var divLeft = document.createElement("div");
      divLeft.className = "left";
      divLeft.id = "prompt" + i;
      if (selected == i) {
        divLeft.className += " selected";
      }
      divLeft.innerHTML = "<code>" + prompt[i]["prompt"] + "</code><br><br><span class=\"name\">" + prompt[i]["name"] + "</span>";
      divLeft.addEventListener('click', updatePrompt);
      div.appendChild(divLeft);
      add.appendChild(div);
      if (i + 1 < prompt.length) {
        var divRight = document.createElement("div");
        divRight.className = "right";
        divRight.id = "prompt" + (i + 1);
        if (selected == i + 1) {
          divRight.className += " selected";
        }
        divRight.innerHTML = "<code>" + prompt[i + 1]["prompt"] + "</code><br><br><span class=\"name\">" + prompt[i + 1]["name"] + "</span>";
        divRight.addEventListener('click', updatePrompt);
        div.appendChild(divRight);
        add.appendChild(div);
      }
      i += 2;
    }
  }
  getSelected();
});
