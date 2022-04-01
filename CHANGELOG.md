# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- Limited max building erorrs to 100
- uint_least24_t type for function UC_Ucs4UpperBytes
- Pretty compiler options' checking output
- More warnings
- Build for Windows on Linux

### Changed
- Hide macro values in documentation.
- Pretty checking messages while configuring
- Better C89 support

### Fixed
- Description for macro UC_VERSION.
- Checking build type for testing

### Removed
- Old test.c since pre-Cmocka times
- Annoying -Wanalyzer-too-complex warning

## [1.0.1] - 2020-05-07
### Added
- CHANGELOG.md file for tracking changes.

### Fixed
- Incorrect commands for building in README.md.

## [1.0.0] - 2020-05-07
### No changelog

## [0.1.0] - 2020-03-18
### No changelog

[Unreleased]: https://github.com/edomin/libuc/compare/v1.0.1...HEAD
[1.0.1]: https://github.com/edomin/libuc/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/edomin/libuc/compare/v0.1.0...v1.0.0
[0.1.0]: https://github.com/edomin/libuc/releases/tag/v0.1.0

