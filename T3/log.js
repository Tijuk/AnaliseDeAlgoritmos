const baseColors = {
    Reset: '\x1b[0m',
    Bright: '\x1b[1m',
    Dim: '\x1b[2m',
    Underscore: '\x1b[4m',
    Blink: '\x1b[5m',
    Reverse: '\x1b[7m',
    Hidden: '\x1b[8m',

    FgBlack: '\x1b[30m',
    FgRed: '\x1b[31m',
    FgGreen: '\x1b[32m',
    FgYellow: '\x1b[33m',
    FgBlue: '\x1b[34m',
    FgMagenta: '\x1b[35m',
    FgCyan: '\x1b[36m',
    FgWhite: '\x1b[37m',

    BgBlack: '\x1b[40m',
    BgRed: '\x1b[41m',
    BgGreen: '\x1b[42m',
    BgYellow: '\x1b[43m',
    BgBlue: '\x1b[44m',
    BgMagenta: '\x1b[45m',
    BgCyan: '\x1b[46m',
    BgWhite: '\x1b[47m',
}

const colors = {
    ...baseColors,
    FgLightRed: baseColors.FgRed + baseColors.Bright,
}

class Log {
    success(text) {
        this.print(`${colors.FgGreen}[ Success ]: ${colors.Reset}${text}`)
        return this
    }

    error(text) {
        this.print(`${colors.FgLightRed}[ Error ]: ${colors.Reset}${text}`)
        return this
    }

    info(text) {
        this.print(`${colors.Bright}[ Info ]: ${text}`)
        return this
    }

    warn(text) {
        this.print(`${colors.BgYellow}[ Error ]: ${colors.Reset}${text}`)
        return this
    }

    catch(text) {
        this.print(
            `${colors.FgLightRed}${colors.Reset}${
                colors.FgLightRed
            }[ Error ]: ${text}`
        )
        return this
    }

    split() {
        const bg = colors.FgBlack
        const fg = colors.Bright
        const splitStr = '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
        return this.print(`${bg + fg}${splitStr}${colors.Reset}`)
    }

    testColors() {
        Object.values(colors).forEach(color => {
            this.print(
                `${colors.FgBlack}${color}sample text _ yeye 190231984 !(@#!@)${
                    colors.Reset
                }`
            )
        })
    }

    print(text) {
        // console.log(text + colors.Reset)
        return this
    }
}

module.exports = new Log()
