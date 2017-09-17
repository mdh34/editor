
all:
	xcodebuild -scheme editor build

clean:
	xcodebuild -scheme editor clean

run:
	xcodebuild -scheme editor build
	./bin/macos/debug/editor
