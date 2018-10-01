let ComponentSelector = document.getElementById("ComponentSelector");

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