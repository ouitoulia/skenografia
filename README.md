# Skenografia

![GitHub](https://img.shields.io/github/license/ouitoulia/skenografia?style=for-the-badge)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/ouitoulia/skenografia?sort=semver&style=for-the-badge)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ouitoulia/skenografia/create-release.yml?style=for-the-badge)

![Packagist Dependency Version](https://img.shields.io/packagist/dependency-v/ouitoulia/skenografia/drupal/bootstrap_italia?style=for-the-badge&logo=drupal)
![Libraries.io dependency status for latest release](https://img.shields.io/github/package-json/dependency-version/ouitoulia/skenografia/bootstrap-italia?style=for-the-badge&logo=github)

![Packagist Downloads](https://img.shields.io/packagist/dt/ouitoulia/skenografia?style=for-the-badge&label=Composer%20DOWNLOADS)
![NPM Downloads](https://img.shields.io/npm/dt/%40ouitoulia%2Fskenografia?style=for-the-badge&label=NPM%20DOWNLOADS&logo=npm)


Skenografia è un sub-theme drupal, basato su [bootstrap_italia](https://drupal.org/project/bootstrap_italia), progettato per implementare il design delle scuole.

## Architettura dei contenuti
Skenografia rappresenta il frontend dell'[architettura dei contenuti delle scuole v1](https://designers.italia.it/modelli/scuole/adotta-il-modello-di-sito-scolastico/definisci-architettura-e-contenuti/)
mentre il backend è gestito dal modulo [ouitoulia/themethla](https://github.com/ouitoulia/themethla/).

## Interfaccia Utente (UI)
L'interfaccia grafica è basata sui [I template HTML](https://designers.italia.it/modelli/scuole/adotta-il-modello-di-sito-scolastico/realizza-l-interfaccia-del-sito-scolastico/)
sviluppati da Designer Italia.

Skenografia aggiorna i Template HTML dalla versione 1.6 di Bootstrap Italia alla versione 2,
rendendo il tema compatibile con Bootstrap 5.2.

### Componenti
Rispetto al repository [Design scuola pagine statiche](https://github.com/italia/design-scuole-pagine-statiche)
il tema usa componenti - menu, card, header, footer, ecc. - conformi a ![Libraries.io dependency status for latest release](https://img.shields.io/github/package-json/dependency-version/ouitoulia/skenografia/bootstrap-italia?style=flat&logo=github)
al posto di `bootstrap-italia:1.6`.

### Librerie CSS/JS
Rispetto al repository [Design scuola pagine statiche](https://github.com/italia/design-scuole-pagine-statiche)
gli stili CSS e i componenti JavaScript sono stati riscritti per essere conformi a ![Libraries.io dependency status for latest release](https://img.shields.io/github/package-json/dependency-version/ouitoulia/skenografia/bootstrap-italia?style=flat&logo=github)
al posto di `bootstrap-italia:1.6`.

La differenza più rilevante rispetto agli assets pubblicati nel repo [Design scuola pagine statiche](https://github.com/italia/design-scuole-pagine-statiche),
oltre alla compatibilità alla versione 2 di bootstrap-italia, riguarda il design del software.
Dal punto di vista del design, è stato abbandonato l'approccio della sovrascrittura
degli stili (noto come "override" e/o "on top") in favore di un'implementazione
più efficiente e scalabile.
Skenografia adotta un sistema di build dinamico, il processo di sviluppo si basa
sulla modifica delle variabili di bootstrap-italia per poi compilare la variante di
bootstrap-italia con il design delle scuole.
Questo approccio non solo migliora le prestazioni, ma anche la manutenibilità del codice,
consentendo al progetto un'espansione più fluida, gestibile e riusabile.

### Distribuzione

![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/ouitoulia/skenografia?sort=semver)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/ouitoulia/skenografia/create-release.yml)
![Packagist Downloads](https://img.shields.io/packagist/dt/ouitoulia/skenografia?label=Composer%20downloads)
![NPM Downloads](https://img.shields.io/npm/dt/%40ouitoulia%2Fskenografia?label=NPM%20downloads&logo=npm)

I sorgenti SCSS e JavaScript vengono caricati automaticamente su npm per agevolare il
riutilizzo e la personalizzazione da parte degli sviluppatori. Inoltre attraverso l'uso delle
GitHub Actions, le librerie vengono automaticamente compilate e distribuite su diverse CDN
in modo che siano già pronte per la produzione.

- https://github.com/ouitoulia/skenografia/releases/latest (build produzione e sorgenti tema)
- https://www.npmjs.com/package/@ouitoulia/skenografia (sorgenti scss e js)
- https://www.jsdelivr.com/package/npm/@ouitoulia/skenografia (build produzione)
- https://classic.yarnpkg.com/en/package/@ouitoulia/skenografia (build produzione)
- https://unpkg.com/browse/@ouitoulia/skenografia@1.20.0/ (sorgenti scss e js e build produzione)

## Contributori, dipendenze ed altre informazioni
- [Contributori di Skenografia](https://github.com/ouitoulia/skenografia/graphs/contributors)
- [Elenco delle dipendenze di Skenografia](https://github.com/ouitoulia/skenografia/network/dependencies)

## Licenze software dei componenti di terze parti
### Componenti distribuiti con Skenografia

Vengono di seguito elencate le licenze dei componenti distribuiti (fonte: [package.json/dependencies](package.json))
- [Bootstrap Italia 2](https://italia.github.io/bootstrap-italia/) © Team per la Trasformazione Digitale, licenza BSD
- [Design scuole pagine statiche](https://github.com/italia/design-scuole-pagine-statiche) © Team per la Trasformazione Digitale, licenza BSD
- [Hamburgers](https://jonsuh.com/hamburgers/) © Jonathan Suh, licenza MIT

### Principali dipendenze per la fase di compilazione e sviluppo
Vengono di seguito elencate le licenze dei componenti usati per lo sviluppo (fonte: [package.json/devDependencies](package.json))
- [clean-webpack-plugin](https://github.com/johnagan/clean-webpack-plugin) © PonteLabs, licenza MIT
- [copy-webpack-plugin](https://github.com/webpack-contrib/copy-webpack-plugin) © webpack-contrib, licenza MIT
- [cross-env](https://github.com/kentcdodds/cross-env) © Kent C. Dodds, licenza MIT
- [css-loader](https://github.com/webpack-contrib/css-loader) © webpack-contrib, licenza MIT
- [mini-css-extract-plugin](https://github.com/webpack-contrib/mini-css-extract-plugin) © webpack-contrib, licenza MIT
- [postcss-loader](https://github.com/webpack-contrib/postcss-loader) © webpack-contrib, licenza MIT
- [rimraf](https://github.com/isaacs/rimraf) © Isaac Z. Schlueter, licenza ISC
- [sass](https://github.com/sass/sass) © sass, licenza MIT
- [sass-loader](https://github.com/webpack-contrib/sass-loader) © webpack-contrib, licenza MIT
- [semver](https://github.com/npm/node-semver) © npm, licenza ISC
- [style-loader](https://github.com/webpack-contrib/style-loader) © webpack-contrib, licenza MIT
- [svg-sprite-loader](https://github.com/kisenka/svg-sprite-loader) © kisenka, licenza MIT
- [svgo-loader](https://github.com/svg/svgo-loader) © epegzz, licenza MIT
- [webpack](https://github.com/webpack/webpack) © webpack, licenza MIT
- [webpack-cli](https://github.com/webpack/webpack-cli) © webpack, licenza MIT
- [webpack-dev-server](https://github.com/webpack/webpack-dev-server) © webpack, licenza MIT
- [webpack-merge](https://github.com/survivejs/webpack-merge) © sounisi5011, licenza MIT

## License
![GitHub](https://img.shields.io/github/license/ouitoulia/skenografia)

Copyright (C) 2023/2024 https://github.com/ouitoulia

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

Questo è un software libero: puoi ridistribuirlo e/o modificarlo secondo i termini della GNU General Public License versione 3 pubblicata dalla Free Software Foundation.

Questo programma è distribuito nella speranza che possa essere utile, ma SENZA ALCUNA GARANZIA; senza nemmeno la garanzia implicita di COMMERCIABILITÀ o IDONEITÀ PER UNO SCOPO PARTICOLARE. Vedere la GNU General Public License per maggiori dettagli.

Questo software è distribuito sotto i termini della GNU Affero General Public License versione 3 (AGPL-3.0)
