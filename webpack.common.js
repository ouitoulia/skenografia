import fs from 'fs/promises';
import MiniCssExtractPlugin from 'mini-css-extract-plugin';
import CopyWebpackPlugin from 'copy-webpack-plugin';
import SvgChunkWebpackPlugin from 'svg-chunk-webpack-plugin';
import paths from './webpack.paths.js';
import semver from 'semver';
import packageJson from './package.json' assert { type: 'json' };

if (!semver.satisfies(process.version, packageJson.engines.node)) {
  throw new Error(`The current Node.js version (${process.version}) does not satisfy the required version (${packageJson.engines.node}).`);
}

export default {
  // Entry
  entry: {
    "bootstrap-italia": [paths.src + '/js/index.js', paths.src + '/scss/theme.scss'],
    "ckeditor5": paths.src + '/scss/ckeditor5.scss',
    "fonts": paths.src + '/scss/_fonts.scss',
    "search-api--submit-filters": [paths.src + '/js/custom/search-api--submit-filters.js'],
    "toc_js_loader": [paths.src + '/js/custom/toc_js.js'],
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
          //paths.modules + '/design-scuole-pagine-statiche/src/assets/icons',
          paths.src + '/icons',
          paths.src + '/svg',
          paths.modules + '/design-scuole-pagine-statiche/src/assets/img'
        ],
        use: [
          {
            loader: SvgChunkWebpackPlugin.loader,
          },
        ],
      },
      // Uncomment if you use loading fonts vi CSS https://git.drupalcode.org/project/bootstrap_italia#loading-fonts-via-css-advanced-users
      {
        test: /\.(woff|woff2|eot|ttf|svg)$/,
        include: [
          paths.modules + '/bootstrap-italia/src/fonts',
        ],
        type: 'asset/resource',
        generator: {
          filename: 'fonts/[name]/[name][ext]',
        },
      },
    ],
  },
  plugins: [
    new MiniCssExtractPlugin({
      filename: 'css/[name].min.css',
      chunkFilename: 'css/[id].min.css'
    }),
    new SvgChunkWebpackPlugin({
      filename: 'svg/sprites.svg',
      svgstoreConfig: {
        svgAttrs: {
          'xmlns': 'http://www.w3.org/2000/svg',
        }
      }
    }),
    new CopyWebpackPlugin({
      patterns: [
        {
          from: paths.modules + '/bootstrap-italia/src/assets/',
          to: paths.build + '/assets/'
        },
        // Lascia commentato per non duplicare i fonts nella cartella dist
        // {
        //   from: paths.modules + '/bootstrap-italia/src/fonts/',
        //   to: paths.build + '/fonts/'
        // },
        {
          from: './src/images/',
          to: paths.build + '/images/'
        },
        {
          from: paths.modules + '/design-scuole-pagine-statiche/src/assets/css/ajax-loader.gif',
          to: paths.build + '/css/ajax-loader.gif'
        },
        {
          from: paths.modules + '/design-scuole-pagine-statiche/src/assets/css/images/',
          to: paths.build + '/css/images/'
        },
        {
          from: paths.modules + '/design-scuole-pagine-statiche/src/assets/img/',
          to: paths.build + '/img/'
        },
        {
          from: paths.modules + '/design-scuole-pagine-statiche/src/assets/placeholders/',
          to: paths.build + '/placeholders/'
        },
        {
          from: paths.modules + '/design-scuole-pagine-statiche/src/assets/svg/',
          to: paths.build + '/svg/'
        },
        {
          from: './version.css',
          to: paths.build + '/css/version.css'
        }
      ]
    }),
    {
      apply: (compiler) => {
        compiler.hooks.afterEmit.tapPromise('AfterEmitPlugin', async (compilation) => {
          const ckeditorJsFile = `${compiler.options.output.path}/js/ckeditor5.min.js`;
          try {
            await fs.rm(ckeditorJsFile, { force: true });
          } catch (err) {
            console.error('Error deleting ckeditor5.min.js:', err);
          }
        });
      },
    },
  ],
};
