const fs = require('fs')
const MiniCssExtractPlugin = require('mini-css-extract-plugin')
const CopyWebpackPlugin = require('copy-webpack-plugin')
const SpriteLoaderPlugin = require('svg-sprite-loader/plugin')
const rimraf = require('rimraf')
const check = require('./webpack.check')

const paths = require('./webpack.paths')

module.exports = {
  // Entry
  entry: {
    "bootstrap-italia": [paths.src + '/js/index.js', paths.src + '/scss/theme.scss'],
    "ckeditor5": paths.src + '/scss/ckeditor5.scss',
    "toc_js_loader": [paths.src + '/js/custom/toc_js.js']
  },

  // Output
  output: {
    path: paths.build,
    filename: "js/[name].min.js",
  },
  module: {
    rules: [
      {
        test: /\.svg$/,
        include: [
          paths.modules + '/bootstrap-italia/src/svg',
          paths.src + '/svg',
          paths.modules + '/design-scuole-pagine-statiche/src/assets/icons'
        ],
        use: [
          {
            loader: 'svg-sprite-loader',
            options: {
              extract: true,
              outputPath: '/svg/',
              spriteFilename: 'sprites.svg',
            }
          },
          {
            loader: 'svgo-loader',
            options: {
              plugins: [
                {
                  name: 'removeAttrs',
                  params: {
                    attrs: '(fill)',
                  },
                }
              ]
            }
          }
        ],
      },
    ],
  },
  plugins: [
    new MiniCssExtractPlugin({
      filename: 'css/[name].min.css',
      chunkFilename: 'css/[id].min.css'
    }),
    new SpriteLoaderPlugin({
      plainSprite: true
    }),
    new CopyWebpackPlugin({
      patterns: [
        {
          from: paths.modules + '/bootstrap-italia/src/assets/',
          to: paths.build + '/assets/'
        },
        {
          from: './src/images/',
          to: paths.build + '/images/'
        },
        {
          from:  paths.modules + '/design-scuole-pagine-statiche/src/assets/css/images/',
          to: paths.build + '/css/images/'
        },
        {
          from:  paths.modules + '/design-scuole-pagine-statiche/src/assets/css/ajax-loader.gif',
          to: paths.build + '/css/ajax-loader.gif'
        },
        {
          from:  paths.modules + '/design-scuole-pagine-statiche/src/assets/img/',
          to: paths.build + '/img/'
        },
        {
          from:  paths.modules + '/design-scuole-pagine-statiche/src/assets/placeholders/',
          to: paths.build + '/placeholders/'
        },
        {
          from:  paths.modules + '/design-scuole-pagine-statiche/src/assets/svg/',
          to: paths.build + '/svg/'
        }
      ]
    }),
    {
      apply: (compiler) => {
        compiler.hooks.afterEmit.tap('AfterEmitPlugin', (compilation) => {
          const ckeditorJsFile = compiler.options.output.path + '/js/ckeditor5.min.js';
          const ckeditorComuniJsFile = compiler.options.output.path + '/js/ckeditor5-comuni.min.js';
          if (fs.existsSync(ckeditorJsFile)) {
            rimraf.sync(ckeditorJsFile);
          }
          if (fs.existsSync(ckeditorComuniJsFile)) {
            rimraf.sync(ckeditorComuniJsFile);
          }
        });
      },
    }
  ],
};
