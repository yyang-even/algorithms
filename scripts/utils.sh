GetProjectRootDir() {
    git rev-parse --show-toplevel
}

GetAllReferenceURLs() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"
    git grep --only-matching -E "[^ ]+://[^ ]+" -- */ | cut -d ":" -f 3-
    QuietRun popd
}
