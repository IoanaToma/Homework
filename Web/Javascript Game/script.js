var generate = function (max) {
  max = max || 5;
  return Math.floor(Math.random() * max);
};

var mainWindow;
var colors;
var userChoice;
var instructionsContainer;
var radioBoxContainer;
var numberOfBoxes;

window.onload = function () {
  userChoice = [];
  colors = ['#2abb67', '#e74c3c', '#BF55EC', '#ecf0f1', '#16a085', '#2c3e50', '#f39c12', '#2980b9', '#D24D57', '#bdc3c7', '#E08283', '#59ABE3',  '#913D88', '#03C9A9', '#FDE3A7', '#C8F7C5', '#F9690E', '#F62459', '#1F3A93', '#AEA8D3'];
  var body = document.body;

  var banner = document.createElement('div');
  var colorBox = document.createElement('div');
  colorBox.className = 'color-box circle';
  colorBox.style.backgroundColor = 'black';
  colorBox.style.marginLeft = '100px';
  colorBox.setAttribute('id', 'banner');

  var direction = 'right';
  banner.appendChild(colorBox);
  body.appendChild(banner);

  var step = 0;
  var banner = document.getElementById('banner');
  var windowWidth = document.body.clientWidth;

  setInterval(function () {
    if (step % 5 === 0) {
      banner.style.backgroundColor = colors[generate(colors.length)];
    }

    if (direction === 'right') {
      step++;
      var currentMarginLeft = banner.style.marginLeft;
      currentMarginLeft = currentMarginLeft.split('p');
      currentMarginLeft = parseInt(currentMarginLeft[0]);
      newMarginLeft = currentMarginLeft + 30;

      banner.style.marginLeft = newMarginLeft + 'px';
      // console.log(windowWidth, newMarginLeft);
      if (windowWidth - newMarginLeft < 130) {
        direction = 'left';
      }
    }

    if (direction === 'left') {
      step++;
      var currentMarginLeft = banner.style.marginLeft;
      currentMarginLeft = currentMarginLeft.split('p');
      currentMarginLeft = parseInt(currentMarginLeft[0]);
      newMarginLeft = currentMarginLeft - 30;

      banner.style.marginLeft = newMarginLeft + 'px';
      if (newMarginLeft < 100) {
        direction = 'right';
      }
    }
  }, 200);


  mainWindow = document.createElement('div');
  mainWindow.setAttribute('id', 'mainWindow');
  body.appendChild(mainWindow);
    
  instructionsContainer = document.createElement('div');
  instructionsContainer.style.marginLeft = '0.5em';
  instructionsContainer.style.marginTop = '0.5em';
  var instructions = document.createElement('span');
  instructions.innerHTML = "Instructiuni: Acesta este un joc pentru doua persoane. Primul jucator trebuie sa aleaga 4 culori (dand click pe o anumita culoare, aceasta se selecteaza; dand click a doua oara pe aceeasi culoarea, aceasta se deselecteaza) si un nume. Apasand pe start, va aparea o fereastra pentru al doilea jucator. Acesta va avea 5 incercari sa gaseasca culorile. Culorile pot fi selectate cu tasta enter. Miscarea intre culorile se face cu sagetile stanga-dreapta. Distractie placuta!";
  instructionsContainer.appendChild(instructions);
  mainWindow.appendChild(instructionsContainer);
    
  var userNameContainer = document.createElement('div');
  userNameContainer.setAttribute('id', 'player-name');
  userNameContainer.style.marginTop = '1em';
  userNameContainer.style.marginBottom = '1em';
  var userName = document.createElement('span');
  userName.innerHTML = "Nume: ";
  var userNameInput = document.createElement('input');
  userNameInput.setAttribute('id', 'player1-name-input');

  userNameContainer.appendChild(userName);
  userNameContainer.appendChild(userNameInput);
  mainWindow.appendChild(userNameContainer);
    
  radioBoxContainer = document.createElement('div');  
  var option = document.createElement('p');
  option.innerHTML = "Alegeti cate culori doriti sa va apara: ";
    
  radioBoxContainer.appendChild(option);
  radioBoxContainer.style.marginLeft = '0.5em';
  radioBoxContainer.style.marginTop = '1em';
  radioBoxContainer.style.marginBottom = '1em';
    
  var radioButtons = [];
    
  for (var i = 6; i <= 10; i = i + 2) {
    var radioButton = document.createElement('input');
    radioButton.setAttribute('type', 'radio');
    radioButton.setAttribute('value', i);
    radioButton.setAttribute('name', 'numberBoxes');
    radioButtons.push(radioButton);
    radioBoxContainer.appendChild(radioButton);
    var text = document.createElement('p');
    text.className = 'optionText'; 
    text.innerHTML = " " + i + "<br>";
    radioBoxContainer.appendChild(text);
  }
    
  var chooseButton = document.createElement('button');
  chooseButton.innerHTML = "Alege";
  chooseButton.setAttribute('id', 'chooseButton');
  chooseButton.style.marginBottom = '1em';
    
  mainWindow.appendChild(radioBoxContainer);
  mainWindow.appendChild(chooseButton);
    
  chooseButton.addEventListener('click', function() {
    for(var i = 0; i < radioButtons.length; i++)
        if(radioButtons[i].checked) 
            numberOfBoxes = parseInt(radioButtons[i].value);
    mainFunction();
  });

};


function mainFunction() {
  numberOfBoxes = numberOfBoxes || 6;
    
  var colorBoxContainer = document.createElement('div');
  colorBoxContainer.setAttribute('id', 'color-box-container');

  var choiceWindow = document.createElement('div');
  choiceWindow.className = 'window-choice';
  choiceWindow.appendChild(colorBoxContainer);

  var usedColors = [];
  var selectedColors = 0;
  for (var i = 0; i < numberOfBoxes; i++) {
    var colorNumber = generate(colors.length);

    while (usedColors.indexOf(colors[colorNumber]) != -1) 
      colorNumber = generate(colors.length);

    var colorBox = document.createElement('div');
    colorBox.className = 'color-box';
    colorBox.style.backgroundColor = colors[colorNumber];
    colorBox.setAttribute('data-color', colors[colorNumber]);

    usedColors.push(colors[colorNumber]);
    colorBoxContainer.appendChild(colorBox);

    colorBox.addEventListener('click', function () {
      var chosenBox = userChoice.indexOf(this.getAttribute('data-color'));

      if (chosenBox > -1) {
        userChoice.splice(chosenBox, 1);
        this.style.borderColor = 'transparent';
        if (selectedColors > 0) {
          selectedColors--;
        }
      } else {
        if (selectedColors >= 4) {
          alert('Ai ales suficiente culori!');
          return;
        }
        userChoice.push(this.getAttribute('data-color'));
        this.style.borderColor = 'red';
        selectedColors++;
      }

      // console.log('selected:', selectedColors, userChoice);
    });
  }

  var player1;
  var showGameButton = document.createElement('button');
  showGameButton.style.marginTop = '1em';
  showGameButton.style.display = 'block';
  showGameButton.className = 'show-game';
  showGameButton.innerHTML = 'Start';

  showGameButton.addEventListener('click', function () {
    if (selectedColors < 4) {
      alert('Selecteaza 4 culori!');
      return;
    }

    player1 = document.getElementById('player1-name-input').value;
    var colorBoxContainer = document.getElementById('color-box-container');

    var alertMsg = document.createElement('h1');
    // alertMsg.className = 'start-alert-message';
    alertMsg.innerHTML = 'Ai selectat culorile!';
    colorBoxContainer.appendChild(alertMsg);

    var counter = document.createElement('h3');
    counter.innerHTML = 'Jocul va incepe in: 5';
    colorBoxContainer.appendChild(counter);

    setTimeout(function () {
      counter.innerHTML = 'Jocul va incepe in: 4';
    }, 500);
    setTimeout(function () {
      counter.innerHTML = 'Jocul va incepe in: 3';
    }, 1000);
    setTimeout(function () {
      counter.innerHTML = 'Jocul va incepe in: 2';
    }, 1500);
    setTimeout(function () {
      counter.innerHTML = 'Jocul va incepe in: 1';
    }, 2000);
    setTimeout(function () {
      mainWindow.removeChild(colorBoxContainer);
      mainWindow.removeChild(document.getElementById('player-name'));
      mainWindow.removeChild(instructionsContainer);
      mainWindow.removeChild(radioBoxContainer);
      mainWindow.removeChild(chooseButton);
      mainWindow.appendChild(gameWindow);
      document.getElementById('elem-0').style.border = '5px solid yellow';
    }, 2500);
  });

  colorBoxContainer.appendChild(showGameButton);
  mainWindow.appendChild(colorBoxContainer);


  var gameWindow = document.createElement('div');

  for (var i = 0; i < colors.length; i++) {
    var elem =  document.createElement('div');
    elem.setAttribute('id', 'elem-' + i);
    elem.className = 'color-box';
    elem.style.backgroundColor = colors[i];
    elem.setAttribute('data-color', colors[i]);
    gameWindow.appendChild(elem);
  }

  var currentElem = 0;
  var selectedBoxes = [];
  window.addEventListener('keydown', function (e) {
    if (e.keyCode === 39) {
      e.preventDefault();
      if (currentElem > colors.length - 2) {
        return;
      } else {
        if (!document.getElementById('elem-' + currentElem).getAttribute('data-selected')) {
          document.getElementById('elem-' + currentElem).style.border = '5px solid transparent';
        }
        else {
          document.getElementById('elem-' + currentElem).style.border = '5px solid red';
        }
        currentElem++;
        var currentSelectedElem = document.getElementById('elem-' + currentElem);
        currentSelectedElem.style.border = '5px solid yellow';
      }
    }

    if (e.keyCode === 37) {
      e.preventDefault();
      if (currentElem < 1) {
        return;
      } else {
        if (!document.getElementById('elem-' + currentElem).getAttribute('data-selected')) {
          document.getElementById('elem-' + currentElem).style.border = '5px solid transparent';
        }
        else {
          document.getElementById('elem-' + currentElem).style.border = '5px solid red';
        }
        currentElem--;
        var currentSelectedElem = document.getElementById('elem-' + currentElem);
        currentSelectedElem.style.border = '5px solid yellow';
      }
    }

    if (e.keyCode === 13) {
      e.preventDefault();
      var elemContainer = document.getElementById('elem-' + currentElem);
      var elem = elemContainer.getAttribute('data-color');
      var index = selectedBoxes.indexOf('elem-' + currentElem);
      if (index === -1) {
        if(selectedBoxes.length < 4) {
          selectedBoxes.push('elem-'+ currentElem);
          elemContainer.style.border = '5px solid red';
          elemContainer.setAttribute('data-selected', true);
        }
        else
          alert('Ai ales deja 4 culori!');
      }
      else {
        selectedBoxes.splice(index, 1);
        elemContainer.removeAttribute('data-selected');
      }
      // console.log('selectedBoxes', selectedBoxes);
    }
  });

  var userTries = 0;
  var maxTries = 5;
  var guessed;
  var submitButton = document.createElement('div');
  submitButton.className = 'submitButton';
  submitButton.innerHTML = 'Verifica';
  submitButton.style.display = 'block';
  submitButton.style.marginTop = '1em';

  submitButton.addEventListener('click', function () {
    if (selectedBoxes.length < 4) {
      alert('Nu ai selectat 4 culori!');
      return;
    }
    userTries++;

    var boxContainer = document.createElement('div');

    var tryText = document.createElement('h4');
    tryText.innerHTML = "Incercarea: " + userTries;
    boxContainer.appendChild(tryText);

    for (var i = 0; i < selectedBoxes.length; i++) {
      var box = document.createElement('div');

      box.className = 'color-box circle';
      box.style.backgroundColor = document.getElementById(selectedBoxes[i]).getAttribute('data-color');
      boxContainer.appendChild(box);
    }

    selectedContainer.appendChild(boxContainer);
    if (selectedBoxes.length > 0) {
      for (i = 0; i < selectedBoxes.length; i++) {
        var index = userChoice.indexOf(document.getElementById(selectedBoxes[i]).getAttribute('data-color'));
        // console.log(selectedBoxes[i], index);
        if (index === -1) {
          document.getElementById(selectedBoxes[i]).style.border = '5px solid transparent';
          document.getElementById(selectedBoxes[i]).removeAttribute('data-selected');
          // console.log('a', selectedBoxes)
          selectedBoxes.splice(i, 1);
          // console.log('b', selectedBoxes);
          i--;
        }
      }
    }
    // console.log('tries', userTries);
    var currentDate = new Date (Date.now());
    if (selectedBoxes.length === userChoice.length) {
      guessed = true;
      alert('Felicitari! (dar nu prea multe ca te obisnuiesti)\n' + 'Astazi, ' + currentDate.getDate() + '.' + currentDate.getMonth() + ' la ora ' + currentDate.getHours() + '\n'+ (player1 || 'Șefu\'') + ' a fost infrant');
      window.location.reload();
      return;
    }
    if (userTries === maxTries && !guessed) {
      alert('Pacat!\n' + 'Astazi, ' + currentDate.getDate() + '.' + currentDate.getMonth() + ' la ora ' + currentDate.getHours() + '\n' + (player1 || 'Șefu\'') + ' te-a caftit!');
      window.location.reload();
      return;
    }
  });

  var selectedContainer = document.createElement('div');
  gameWindow.appendChild(submitButton);
  gameWindow.appendChild(selectedContainer);
}