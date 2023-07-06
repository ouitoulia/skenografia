// Importa le icone custom dalla cartella src/svg/
const iconsCustom = require.context('../../svg', false, /\.svg$/);
iconsCustom.keys().forEach(svgFile => {
  let svg = iconsCustom(svgFile);
});

// Importa le icone dalla dipendenza design-scuole-pagine-statiche#main
const iconsScuolePagineStatiche = require.context('design-scuole-pagine-statiche/src/assets/icons', false, /\.svg$/);
iconsScuolePagineStatiche.keys().forEach(svgFile => {
  let svg = iconsScuolePagineStatiche(svgFile);
});
