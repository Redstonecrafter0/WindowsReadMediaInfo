#include <iostream>
#include <vector>
#include <fstream>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>

using namespace winrt;
using namespace Windows::Media::Control;
using namespace Windows::Storage::Streams;

int main() {
    GlobalSystemMediaTransportControlsSessionManager smtc = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
    auto sessions = smtc.GetSessions();
    for (int i = 0; i < sessions.Size(); ++i) {
        auto session = sessions.GetAt(i);
        auto mediaProps = session.TryGetMediaPropertiesAsync().get();
        auto title = to_string(mediaProps.Title());
        auto artist = to_string(mediaProps.Artist());
        auto thumbnail = mediaProps.Thumbnail().OpenReadAsync().get();
        auto reader = DataReader(thumbnail.GetInputStreamAt(0));
        reader.LoadAsync(thumbnail.Size()).get();
        std::vector<uint8_t> buffer(thumbnail.Size());
        auto bufferView = array_view<uint8_t>(buffer);
        reader.ReadBytes(bufferView);
        reader.Close();
        std::ofstream file("thumbnail.png", std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
        file.close();
        std::cout << title << std::endl;
        std::cout << artist << std::endl;
    }
    return 0;
}
