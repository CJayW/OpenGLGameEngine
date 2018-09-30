//let comp = document.getElementById("ComponentBody");

//let Position = new vec3(comp, "Position");
//let Rotation = new vec3(comp, "Rotation");
//let Scale = new vec3(comp, "Scale");

// document.addEventListener("keydown", (e)=>{
//     if(e.key == "p"){
//         console.log(Position.getX());
//     }
// })

let transform = new Transform();

document.addEventListener("keydown", (e)=>{
    if(e.key == "p"){
        console.log(transform.toString());      
    }
})