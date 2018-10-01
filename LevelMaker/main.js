let ComponentSelector = document.getElementById("ComponentSelector");

let options = "";
for(let i = 1; i < componentTypes.length; i++){
    let name = componentTypes[i].split(" ")[0];
    options += '<Option value="' + i + '">' + name + '</Option>'
}
console.log(options);

let option = document.createElement("div");
ComponentSelector.appendChild(option);
option.outerHTML = options;


let GameObjects = [];
GameObjects.push(new GameObject());

function Export(){
    console.log(GameObjects[0].toString());
}

function AddSelectedComponent(){
    GameObjects[0].addComponent(ComponentSelector.value);
}

//components
//Rewrite the toString functions