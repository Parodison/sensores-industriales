const buscarRedesBtn = document.getElementById("buscarRedesBtn")
const buscandoRedesSection = document.querySelector(".buscando-redes-section")
const menuPrincipal = document.getElementById("menu-principal")
const listaWifi = document.querySelector(".lista-wifi")

const listadoWifi = [
    {
        ssid: "Flia_ferreira"
    },
    {
        ssid: "PARODI"
    }
]

buscarRedesBtn.addEventListener("click", () => {
    menuPrincipal.style.display = "none";
    buscandoRedesSection.style.display = "flex";
    setTimeout(() => {
        buscandoRedesSection.style.display = "none";

        const tituloListado = document.createElement("h1");
        tituloListado.style.fontWeight = 600;
        tituloListado.style.textDecoration = "underline";
        tituloListado.innerText = `Se han encontrado ${listadoWifi.length} redes disponibles`

        const ul = document.createElement("ul")
        ul.style.width = "100%";
        ul.style.display = "flex";
        ul.style.flexDirection = "column";
        ul.style.justifyContent = "center";
        ul.style.alignItems = "center";
        ul.style.gap = "10px"
        listadoWifi.map((data, index) => {
            const li = document.createElement("li");
            li.style.flex = 1;
            li.style.display = "flex";
            li.style.flexDirection = "row";
            li.style.justifyContent = "space-between";
            li.style.alignItems = "center";
            li.style.padding = "10px";
            li.style.backgroundColor = "rgba(207, 207, 207, 1)";
            li.style.borderRadius = "10px";
            li.innerHTML = `
                <svg xmlns="http://www.w3.org/2000/svg" height="24px" viewBox="0 -960 960 960" width="24px" fill="#7b7b7bff"><path d="M480-120q-42 0-71-29t-29-71q0-42 29-71t71-29q42 0 71 29t29 71q0 42-29 71t-71 29ZM254-346l-84-86q59-59 138.5-93.5T480-560q92 0 171.5 35T790-430l-84 84q-44-44-102-69t-124-25q-66 0-124 25t-102 69ZM84-516 0-600q92-94 215-147t265-53q142 0 265 53t215 147l-84 84q-77-77-178.5-120.5T480-680q-116 0-217.5 43.5T84-516Z"/></svg>
                
            `
            const h3 = document.createElement("h3")
            h3.style.padding = 0;
            h3.style.margin = 0;
            h3.innerText = data.ssid;
            li.appendChild(h3)

            ul.appendChild(li);
        })

        listaWifi.appendChild(tituloListado);
        listaWifi.appendChild(ul);
        listaWifi.style.display = "flex";
    }, 1000);


})