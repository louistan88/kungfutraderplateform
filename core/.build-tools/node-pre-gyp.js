const {spawnSync} = require("child_process");

function run(cmd, args, title) {
    console.log(`$ ${cmd} ${args.join(' ')}`);
    const result = spawnSync(cmd, args, {
        shell: true,
        stdio: ["inherit", "inherit", "inherit"],
        windowsHide: true
    });
    if (result.status !== 0) {
        console.log(`${title} exited with code ${result.status}`);
        process.exit(result.status);
    }
}

function node_pre_gyp(cmd, argv) {
    const build_type_arg = argv.buildType === "Debug" ? ["--debug"] : [];
    const npx_cmd_arg = ["node-pre-gyp", ...build_type_arg, ...cmd].join(' ');
    run("npx", ["-c", `"${npx_cmd_arg}"`], "node-pre-gyp");
}

const argv = require("yargs/yargs")(process.argv.slice(2))
    .command("install", "install through node-pre-gyp", (yargs) => {
    }, (argv) => {
        node_pre_gyp(["install", "--fallback-to-build"], argv);
    })
    .command("build", "build from source", (yargs) => {
    }, (argv) => {
        node_pre_gyp(["configure", "build"], argv);
    })
    .command("package", "package binary", (yargs) => {
    }, (argv) => {
        node_pre_gyp(["package"], argv);
    })
    .option("build-type", {
        choices: ["Release", "Debug"],
        default: "Release"
    })
    .demandCommand()
    .help()
    .argv;