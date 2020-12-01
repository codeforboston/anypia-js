#  AnyPIA Social Security Calculator javascript port project
## AnyPIA-JS wrapper of the Official C++ AnyPIA

This repository takes the most updated Social Security [Detailed Calculator](https://ssa.gov/OACT/anypia/anypia.html) Windows-based tool, and wraps it with a JSON API, and repackages it using WebAssembly (WASM) so that it can be used as part of a website. No data is sent away from the user's browser.

The affiliated [React app](https://github.com/codeforboston/windfall-elimination/) was created to help retirees affected by the Social Security Windfall Elimination Provision (WEP) understand their benefits with a walkthrough. This Detailed Calculator's results for a retiree are shown as one of two options available in the app.

<img width="800" alt="image" src="https://user-images.githubusercontent.com/283343/100708306-12d66800-337a-11eb-8c58-b3a4551d36c1.png" />

**Example usage of AnyPIA-JS (middle) alongside the original AnyPIA (right) and the React app (left)**


## Documentation
- Deeper [non-technical introduction](https://github.com/codeforboston/windfall-elimination/blob/develop/src/library/pia/README-nontechnical.md) to this effort.
- See technical details of both [AnyPIA-JS and PiaFormat.ts](https://github.com/codeforboston/windfall-elimination/tree/develop/src/library/pia) for use of the (originally Windows-based) Social Security [Detailed Calculator](https://ssa.gov/OACT/anypia/anypia.html) from within your javascript app. 

Also a sister project of https://github.com/bslabs/anypiamac

## Installing and building
- On Windows, Install [Choco](https://chocolatey.org/install) first, then use `.\installbuild-windows.bat`
- Otherwise, run the matching `installbuild-*` script or batch file for your platform and output type: like: `./installbuild-emscripten-anypiab-mac.sh`.
