#pragma once

#include <iostream>
#include <format>
#include <array>
#include <cstdint>
#include <cstring>

template <std::size_t SIZE>
struct MemViewer {
    inline static char constexpr reset[] = "\033[0m";
    inline static char constexpr red[] = "\033[31m";
    inline static char constexpr white[] = "\033[37m";
    inline static char constexpr grey[] = "\033[38;5;236m";

    bool readOutside { true }; // Reads outside of object boundaries. Will crash under memory supervision tools.

    constexpr explicit MemViewer(auto const* pmem) noexcept 
        : PMEM{ reinterpret_cast<std::uint8_t const*>(pmem) } {
        saveMemory();
    }
    constexpr explicit MemViewer(auto const& obj) noexcept : MemViewer(&obj) {}

    constexpr bool insideObjectBoundaries(std::uint8_t const * const pmem) const noexcept {
        return pmem >= PMEM && pmem < END;
    }
    constexpr char const* getColor(std::uint8_t const*pmem, std::uint8_t const *pold) const noexcept {
        if ( insideObjectBoundaries(pmem) ) {
            if (*pmem == *pold) return white;
            else                return red;
        }
        return grey;
    }

    struct Params {
        std::uint8_t const *pmem;
        std::uint8_t const *pold; 
        std::size_t  size { 16 };
        std::uint8_t group_size { 4 };
        std::uint8_t sep { ' ' };
        bool         readOutside { readOutside };
    };

    void showMemoryLineHex(Params p) const noexcept {
        uint8_t grp{0};
        auto const sep_c = std::format(" {:c} ", p.sep);
        auto const sep_nc= std::format(" ");
        auto const* sep = &sep_nc;
        while(p.size) {
            char const* color = getColor(p.pmem, p.pold);
            
            if ( p.readOutside == false && insideObjectBoundaries(p.pmem) == false ) {
                std::cout << std::format("{}{}--", color, *sep, *p.pmem);
            } else {
                std::cout << std::format("{}{}{:02X}", color, *sep, *p.pmem);
            }

            grp += 1; sep = &sep_nc;
            if (grp == p.group_size) { 
                grp = 0;
                sep = &sep_c;
            }
            p.pmem +=1; 
            p.pold +=1;
            p.size -=1;
        }
    }
    void showMemoryLineChar(Params p) const noexcept {
        uint8_t grp{0};
        auto const sep_c = std::format("{:c}", p.sep);
        auto const sep_nc= std::format("");
        auto const* sep = &sep_nc;

        while(p.size) {
            char const* color = getColor(p.pmem, p.pold);
            uint8_t c = '.';
            if ( p.readOutside || insideObjectBoundaries(p.pmem) ) {
                c = (*p.pmem > 31 && *p.pmem < 127) ? *p.pmem : '.';
            }
            std::cout << std::format("{}{}{:c}", color, *sep, c);
            
            grp += 1; sep = &sep_nc;
            if (grp == p.group_size) { 
                grp = 0;
                sep = &sep_c;
            }
            p.pmem += 1; 
            p.pold += 1;
            p.size -= 1;
        }
    }
    void showMemory(std::size_t const width = 16, std::uint8_t const grpsize = 4) const noexcept {
        std::array<uint8_t const, 16> constexpr headnums { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        auto const* pmem = PMEM;
        auto const* pold = memSaved_.data();
        auto lines = SIZE/width;
        lines += (SIZE % width > 0);

        auto const num_seps  = (width / grpsize) - ((width % grpsize == 0) ? 1 : 0);
        auto const linewidth = 89 + 3*num_seps;
        auto const asciiwidth= 16 + num_seps;
        auto const header1   = std::format("||{:^16}||", "ADDRESS"); 
        auto const header2   = std::format("||{:^{}}||", "ASCII", asciiwidth); 
        auto const line      = std::format("{:=<{}s}","=", linewidth);
        
        std::cout << std::format("{}\n{}", line, header1);
        showMemoryLineHex ({.pmem=&headnums[0], .pold=&headnums[0], .size=width, .group_size=grpsize, .readOutside=true});
        std::cout << std::format("{} {}\n{}\n", reset, header2, line);
        while(lines) {
            std::cout << std::format("|| {:14p} ||", (void*)pmem);
            showMemoryLineHex ({.pmem=pmem, .pold=pold, .size=width, .group_size=grpsize}); std::cout << " ||";
            showMemoryLineChar({.pmem=pmem, .pold=pold, .size=width, .group_size=grpsize}); std::cout << "||\n";
            pmem += width; pold += width;
            --lines;
        }
        std::cout << std::format("{}{}\n", reset, line);
    }
    constexpr void print(std::size_t const width = 16) noexcept {
        showMemory(width, 8);
        saveMemory();
        std::cout << reset;
    }
    constexpr void saveMemory() noexcept { std::memcpy(memSaved_.data(), PMEM, SIZE); }
private:
    std::uint8_t const* PMEM{};
    std::uint8_t const* END{PMEM + SIZE};
    std::array<uint8_t, SIZE> memSaved_{};
};

// Deduction guides
template <typename T>
MemViewer(T*) -> MemViewer<sizeof(T)>;
template <typename T>
MemViewer(T&) -> MemViewer<sizeof(T)>;
