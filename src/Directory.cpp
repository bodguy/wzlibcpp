#include "wz/Directory.hpp"

namespace wz {

    Directory::Directory(Reader& from_file, bool img, int new_size, int new_checksum, unsigned int new_offset)
            : image(img), size(new_size), checksum(new_checksum), offset(new_offset), Node(from_file) {
    }

    void wz::Directory::Set(bool img, int new_size, int new_checksum, unsigned int new_offset) {
        image = img;
        size = new_size;
        checksum = new_checksum;
        offset = new_offset;
    }

    u32 wz::Directory::get_offset() const {
        return offset;
    }

    bool wz::Directory::is_image() const {
        return image;
    }

    bool Directory::parse_image(Node* node) {
        if (is_image()) {
            node->reader = reader;

            const auto current_offset = get_offset();
            reader->set_position(current_offset);
            if (reader->is_wz_image()) {
                return parsePropertyList(node, current_offset);
            }
        }
        return false;
    }

}