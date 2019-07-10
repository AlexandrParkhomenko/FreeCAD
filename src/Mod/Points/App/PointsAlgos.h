/***************************************************************************
 *   Copyright (c) Juergen Riegel         <juergen.riegel@web.de>          *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef _PointsAlgos_h_
#define _PointsAlgos_h_

#include "Points.h"
#include "Properties.h"
#include <Eigen/Core>

namespace Points
{

/** The Points algorithms container class
 */
class Standard_EXPORT PointsAlgos
{
public:
    /** Load a point cloud
     */
    static void Load(PointKernel&, const char *FileName);
    /** Load a point cloud
     */
    static void LoadAscii(PointKernel&, const char *FileName);
};

class Reader
{
public:
    Reader();
    virtual ~Reader();
    virtual void read(const std::string& filename) = 0;

    void clear();
    const PointKernel& getPoints() const;
    bool hasProperties() const;
    const std::vector<float>& getIntensities() const;
    bool hasIntensities() const;
    const std::vector<App::Color>& getColors() const;
    bool hasColors() const;
    const std::vector<Base::Vector3f>& getNormals() const;
    bool hasNormals() const;
    bool isStructured() const;
    int getWidth() const;
    int getHeight() const;

protected:
    PointKernel points;
    std::vector<float> intensity;
    std::vector<App::Color> colors;
    std::vector<Base::Vector3f> normals;
    int width, height;
};

class AscReader : public Reader
{
public:
    AscReader();
    ~AscReader();
    void read(const std::string& filename);
};

class PlyReader : public Reader
{
public:
    PlyReader();
    ~PlyReader();
    void read(const std::string& filename);

private:
    std::size_t readHeader(std::istream&, std::string& format, std::size_t& offset,
        std::vector<std::string>& fields, std::vector<std::string>& types,
        std::vector<int>& sizes);
    void readAscii(std::istream&, std::size_t offset, Eigen::MatrixXd& data);
    void readBinary(bool swapByteOrder, std::istream&, std::size_t offset,
        const std::vector<std::string>& types,
        const std::vector<int>& sizes,
        Eigen::MatrixXd& data);
};

class PcdReader : public Reader
{
public:
    PcdReader();
    ~PcdReader();
    void read(const std::string& filename);

private:
    std::size_t readHeader(std::istream&, std::string& format, std::vector<std::string>& fields,
        std::vector<std::string>& types, std::vector<int>& sizes);
    void readAscii(std::istream&, Eigen::MatrixXd& data);
    void readBinary(bool transpose, std::istream&,
        const std::vector<std::string>& types,
        const std::vector<int>& sizes,
        Eigen::MatrixXd& data);
};

class Writer
{
public:
    Writer(const PointKernel&);
    virtual ~Writer();
    virtual void write(const std::string& filename) = 0;

    void setIntensities(const std::vector<float>&);
    void setColors(const std::vector<App::Color>&);
    void setNormals(const std::vector<Base::Vector3f>&);
    void setWidth(int);
    void setHeight(int);
    void setPlacement(const Base::Placement&);

protected:
    const PointKernel& points;
    std::vector<float> intensity;
    std::vector<App::Color> colors;
    std::vector<Base::Vector3f> normals;
    int width, height;
    Base::Placement placement;
};

class AscWriter : public Writer
{
public:
    AscWriter(const PointKernel&);
    ~AscWriter();
    void write(const std::string& filename);
};

class PlyWriter : public Writer
{
public:
    PlyWriter(const PointKernel&);
    ~PlyWriter();
    void write(const std::string& filename);
};

class PcdWriter : public Writer
{
public:
    PcdWriter(const PointKernel&);
    ~PcdWriter();
    void write(const std::string& filename);
};

} // namespace Points


#endif 
