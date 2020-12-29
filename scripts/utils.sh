GetAllReferenceURLs() {
    git grep --only-matching -E "[^ ]+://[^ ]+" -- */ | cut -d ":" -f 3-
}
