#ifndef COVERAGE_ANNOTATION_HPP
#define COVERAGE_ANNOTATION_HPP

#include <string>
#include <vector>
#include <iostream>

namespace coverage {

struct Position {
  int line;
  int column;
};

inline std::ostream& operator<<(std::ostream& stream, const Position& pos) {
  stream << "coverage::Position(" << pos.line << "/" << pos.column << ")";
  return stream;
}

inline bool operator==(const Position& lhs, const Position& rhs) {
  return rhs.line == lhs.line and rhs.column == lhs.column;
}

struct Range {
  Position start;
  Position end;
};

inline std::ostream& operator<<(std::ostream& stream, const Range& range) {
  stream << "coverage::Range(" << range.start << ", " << range.end << ")";
  return stream;
}

inline bool operator==(const Range& lhs, const Range& rhs) {
  return lhs.start == rhs.start and lhs.end == rhs.end;
}

struct Annotation {
  std::string name;
  Range visual;
  Range marker;
};

inline std::ostream& operator<<(std::ostream& stream,
                                const Annotation& annotation) {
  stream << "coverage::Annotation('" << annotation.name << "'\n"
         << "  visual: " << annotation.visual << "\n"
         << "  marker: " << annotation.marker << "\n)";
  return stream;
}

inline bool operator==(const Annotation& lhs, const Annotation& rhs) {
  return lhs.name == rhs.name and lhs.visual == rhs.visual and
         lhs.marker == rhs.marker;
}

typedef std::vector<Annotation> Annotations;
}

#endif
