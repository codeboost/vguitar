#ifndef FRETBOARDMODEL_H
#define FRETBOARDMODEL_H

#include <QRect>
#include <QVector>
#include <QString>

namespace vg
{


    struct FingerHighlight
    {
        int stringNumber = 0;
        int fretNumber = 0;
        //Maybe something else, like color or note name
        FingerHighlight(int stringN = 0, int fretN = 0): stringNumber(stringN), fretNumber(fretN){}
        bool operator == (const FingerHighlight& rhs)
        {
            return rhs.stringNumber == stringNumber &&
                   rhs.fretNumber == fretNumber;
        }
    };

    class FretboardModel
    {
    public:
        int numberOfFrets = 16;
        int numberOfStrings = 6;
        int nutThickness = 20;
        int fretThickness = 4;
        int maxStringThickness = 4;
        int noteNameRadius = 10;

        //The 'common' 6-string guitar note order is used here
        //Other stringed instruments might have different notes, so make sure you configure it properly.
        QString noteNames = "ebgdAE";

        bool shouldDrawNoteNames = true;

        Qt::Orientation orientation = Qt::Horizontal;

        //AscendingOrder: e string on top (or left) , E string on bottom (or right)
        Qt::SortOrder stringOrder = Qt::AscendingOrder;
    public:
        QRect& rect();
        void setRect(const QRect& r);
        //Returns the rect for the fret and string.
        //Fret and strings indices are 1-based.
        //QRect getFretRect(int fretNumber, int stringNumber);
        
        //indices are 0-based
        QPoint intersectionPoint(int fretNumber, int stringNumber);

        float widthForString(int stringIndex);
        void update();

        //Returns the string position for string i (0-based).
        //The value returned may be the horizontal x or vertical y coordinate of the string,
        //depending on the orientation.
        float posForString(int i);

        //Returns the position for fret i (0-based).
        //The value returned may be horizontal or vertical, depending on the orientation.
        float posForFret(int i);

        //Nut starting position, depending on orientation and stringOrder.
        int posForNut();

        //Returns the note name for guitar string i (0-based).
        //The note name returned depends on the stringOrder value.
        QString noteNameForString(int i);

        const QVector<FingerHighlight>& getHighlights() const
        {
            return highlights;
        }

        bool isValidHighlight(const FingerHighlight& highlight)
        {
            if (highlight.stringNumber > numberOfStrings ||
                highlight.fretNumber > numberOfFrets)
            {
                return false;
            }

            return true;
        }

        void addHighlight(const FingerHighlight& highlight)
        {

//            if (highlights.contains(highlight))
//                return;

            if (!isValidHighlight(highlight))
                return;

            highlights.push_back(highlight);
        }


        void clearHighlights()
        {
            highlights.clear();
        }

    protected:
        QRect fretboardRect;
        QVector<float> fretPositions;
        QVector<float> stringPositions;
        QVector<FingerHighlight> highlights;

        void updateFretPositions();
        void updateStringPositions();
    };
}

#endif // FRETBOARDMODEL_H
